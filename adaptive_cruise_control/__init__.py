import serial
import time
import cv2
import numpy as np
import pyrealsense2 as rs
from ultralytics import YOLO

DISTANCE_THRESHOLD = 1.5  # Meters

class AdaptiveCruiseControl:
    def __init__(self, model_path="yolov8n.pt", port="/dev/ttyUSB0"):
        # Load model
        self.model = YOLO(model_path)

        # Setup RealSense
        self.pipeline = rs.pipeline()
        config = rs.config()
        config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
        config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
        self.pipeline.start(config)
        self.align = rs.align(rs.stream.color)

        # Setup serial
        self.arduino = serial.Serial(port, 9600)
        time.sleep(2)

    def get_aligned_frames(self):
        frames = self.pipeline.wait_for_frames()
        aligned = self.align.process(frames)
        return aligned.get_depth_frame(), aligned.get_color_frame()

    def process_frame(self, depth_frame, color_frame):
        color_image = np.asanyarray(color_frame.get_data())
        results = self.model(color_image, verbose=False)[0]

        min_distance = float('inf')

        for box in results.boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])
            mid_x, mid_y = (x1 + x2) // 2, (y1 + y2) // 2
            distance = depth_frame.get_distance(mid_x, mid_y)
            if 0 < distance < min_distance:
                min_distance = distance

            # Draw on frame
            class_id = int(box.cls[0])
            label = self.model.names[class_id]
            cv2.rectangle(color_image, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(color_image, f"{label} {distance:.2f}m", (x1, y1 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

        # Logic
        if min_distance < DISTANCE_THRESHOLD:
            self.arduino.write(b'stop\n')
            cv2.putText(color_image, "WARNING: Object Too Close!", (20, 40),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 3)
        else:
            self.arduino.write(b'go\n')

        return color_image

    def cleanup(self):
        self.pipeline.stop()
        self.arduino.close()
        cv2.destroyAllWindows()
