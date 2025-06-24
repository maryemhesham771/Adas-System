from . import AdaptiveCruiseControl
import cv2

if __name__ == "__main__":
    acc = AdaptiveCruiseControl()

    try:
        while True:
            depth_frame, color_frame = acc.get_aligned_frames()
            if not depth_frame or not color_frame:
                continue

            image = acc.process_frame(depth_frame, color_frame)
            cv2.imshow("Jetson ACC System", image)

            if cv2.waitKey(1) & 0xFF == 27:  # ESC
                break

    finally:
        acc.cleanup()
