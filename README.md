# ADAS‑System

*Last generated: 2025‑06‑21 21:16*

A modular Advanced Driver‑Assistance System (ADAS) project containing:

| Feature | Description |
|---------|-------------|
| Lane‑Keep Assist | Vision‑based lane detection with steering‑servo output. |
| Blind‑Spot Monitor | Dual‑camera motion detection with side indicators. |
| Driver Monitoring | Face / gaze tracking with alerts and safety stop. |

## Repository Layout

```
adas-system/
├── lane_keep_assist/
│   ├── main.py
│   ├── arduino/
│   └── hardware/
├── blind_spot_monitor/
│   └── ...
├── driver_monitoring_system/
│   └── ...
├── requirements.txt
└── README.md
```

## Quick‑Start

```bash
# Create venv & install deps
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### Running Lane‑Keep Assist

```bash
python -m lane_keep_assist.main
```

Similar commands apply for the other features.

## Hardware Connections

Open the `hardware/` folder inside each feature for wiring guides.

## License

MIT
