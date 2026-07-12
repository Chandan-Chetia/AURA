python voice.py
.venv\Scripts\activate

RobotOS/
│
├── main.py                 # Starts the robot
│
├── config.py               # COM port, model names, settings
│
├── perception/
│   ├── hearing.py          # Microphone + Silero VAD
│   ├── stt.py              # Whisper Speech-to-Text
│   ├── vision.py           # Camera (future)
│   └── lidar.py            # Distance sensors (future)
│
├── cognition/
│   ├── llm.py              # Ollama/Qwen
│   ├── planner.py          # AI JSON → robot tasks
│   └── memory.py           # Memory system
│
├── motion/
│   ├── robot.py            # Executes commands
│   ├── wheels.py           # Wheel movement
│   ├── arms.py             # Servo control
│   └── head.py             # Future neck servo
│
├── communication/
│   ├── serial.py           # Arduino USB
│   └── wifi.py             # Future Wi-Fi robot
│
├── speech/
│   ├── tts.py              # Piper
│   └── wakeword.py         # Future wake word
│
├── skills/
│   ├── greet.py
│   ├── dance.py
│   ├── follow.py
│   ├── search.py
│   └── self_intro.py
│
└── models/
    └── piper/# AURA
