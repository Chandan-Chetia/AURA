AI_Robot/
│
├── robot.py          ← Main AI program
├── voice.py          ← Speech recognition
├── ai.py             ← AI command processing
├── serial_comm.py    ← USB communication
├── camera.py         ← Vision (later)
└── arduino/
    └── robot.ino     ← Arduino code

    python serial_comm.py

AI_Robot/
│
├── main.py
├── voice.py
├── speaker.py
├── brain.py
├── serial_comm.py
├── robot.py
│
├── skills/
│   ├── movement.py
│   ├── arms.py
│   ├── conversation.py
│
└── arduino/

AI_Robot
│
├── voice.py          ✅
├── speaker.py        ✅
├── mic.py            ✅
├── serial_comm.py    ✅
├── robot.py
├── ai.py
├── memory.py
└── arduino/
    └── robot.ino

AI_Robot/
│
├── main.py              ← Starts everything
├── voice.py             ← Speech → Text
├── brain.py             ← Ollama (AI)
├── speaker.py           ← Robot voice
├── serial_comm.py       ← Arduino communication
├── robot.py             ← Robot API
├── mic.py
├── memory.py
│
├── skills/
│   ├── movement.py
│   ├── arms.py
│   └── conversation.py
│
└── arduino/

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
