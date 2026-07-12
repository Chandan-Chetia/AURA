import time
from serial_comm import send_command
from speech.speaker import speak

# ---------------------------------
# Robot Personality
# ---------------------------------
def chat(text):
    lower = text.lower()

    # Pick a quick reaction gesture to lead in with (optional, plays before talking starts)
    gesture_cmd = None
    if "hello" in lower or "hi" in lower or "good morning" in lower:
        gesture_cmd = "Z"       # Greet
    elif "thank" in lower:
        gesture_cmd = "X"       # Salute
    elif "awesome" in lower or "great" in lower or "congratulations" in lower or "excited" in lower or "yay" in lower:
        gesture_cmd = "Y"       # Happy animation
    elif "sorry" in lower or "sad" in lower or "unfortunately" in lower:
        gesture_cmd = "w"       # Sad
    elif "no" in lower or "cannot" in lower or "can't" in lower:
        gesture_cmd = "M"       # Shake no
    elif "yes" in lower or "sure" in lower or "okay" in lower or "ok" in lower:
        gesture_cmd = "N"       # Nod yes
    elif "confused" in lower or "what do you mean" in lower or "i don't understand" in lower:
        gesture_cmd = "Q"       # Confused
    elif "hmm" in lower or "thinking" in lower or "let me think" in lower:
        gesture_cmd = "y"       # Thinking

    if gesture_cmd:
        send_command(gesture_cmd)

    # ---- Solution 1: Python decides how long the talk animation runs ----
    send_command("T")      # Start continuous talking animation
    speak(text)            # Kokoro speaks - takes however long it takes
    send_command("t")      # Stop talking animation, return to neutral

# ---------------------------------
# Movement
# ---------------------------------
def move(direction):
    if direction == "forward":
        speak("Moving forward")
        send_command("F")
    elif direction == "back":
        speak("Moving backward")
        send_command("B")

def turn(direction):
    if direction == "left":
        speak("Turning left")
        send_command("L")
    elif direction == "right":
        speak("Turning right")
        send_command("R")

def stop():
    speak("Stopping")
    send_command("S")

# ---------------------------------
# Arms
# ---------------------------------
def arm(side, movement):
    if side == "both":
        if movement == "up":
            speak("Raising both arms")
            send_command("H")
        elif movement == "down":
            speak("Lowering both arms")
            send_command("D")
        return
    if side == "left":
        if movement == "up":
            speak("Raising left arm")
            send_command("a")      # Left servo reversed
        elif movement == "down":
            speak("Lowering left arm")
            send_command("A")
        return
    if side == "right":
        if movement == "up":
            speak("Raising right arm")
            send_command("C")
        elif movement == "down":
            speak("Lowering right arm")
            send_command("c")
        return

# ---------------------------------
# Gripper
# ---------------------------------
def grip(movement):
    if movement == "open":
        speak("Opening gripper")
        send_command("g")
    elif movement == "close":
        speak("Closing gripper")
        send_command("p")
    else:
        speak("I don't know that gripper movement.")

# ---------------------------------
# Head
# ---------------------------------
def head(direction):
    if direction == "up":
        speak("Looking up")
        send_command("i")
    elif direction == "down":
        speak("Looking down")
        send_command("k")
    elif direction == "left":
        speak("Looking left")
        send_command("j")
    elif direction == "right":
        speak("Looking right")
        send_command("l")
    elif direction in ("center", "neutral", "forward"):
        speak("Looking straight ahead")
        send_command("n")
    else:
        speak("I don't know that head movement.")

# ---------------------------------
# Standalone Gestures
# ---------------------------------
GESTURE_COMMANDS = {
    "wave": "W",
    "salute": "X",
    "happy": "Y",
    "nod": "N",
    "shake": "M",
    "scan": "V",
    "curious": "U",
    "greet": "Z",
    "excited": "E",
    "sad": "w",
    "confused": "Q",
    "thinking": "y",
}

def gesture(name):
    cmd = GESTURE_COMMANDS.get(name)
    if cmd:
        speak(f"Doing {name} gesture")
        send_command(cmd)
    else:
        speak("I don't know that gesture.")

# ---------------------------------
# Main Executor
# ---------------------------------
def execute(command):
    if not isinstance(command, dict):
        speak("Invalid command.")
        return

    cmd_type = command.get("type")

    # ---------------- CHAT ----------------
    if cmd_type == "chat":
        chat(command.get("response", ""))
        return

    # ---------------- ACTION ----------------
    if cmd_type != "action":
        speak("I don't understand.")
        return

    action = command.get("action")

    if action == "move":
        move(command.get("direction"))
    elif action == "turn":
        turn(command.get("direction"))
    elif action == "stop":
        stop()
    elif action == "arm":
        arm(
            command.get("side"),
            command.get("movement")
        )
    elif action == "grip":
        grip(command.get("movement"))
    elif action == "head":
        head(command.get("direction"))
    elif action == "gesture":
        gesture(command.get("name"))
    else:
        speak("Sorry, I cannot do that yet.")