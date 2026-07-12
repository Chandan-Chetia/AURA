import time
import whisper
import torch

from mic import record_audio
from cognition.brain import think
from motion.robot import execute

print("Loading Whisper model...")
device = "cuda" if torch.cuda.is_available() else "cpu"

print("Using:", device)

model = whisper.load_model("small", device=device)
print("Robot Ready!")


while True:

    # 1. Record
    t1 = time.time()
    filename = record_audio()
    print(f"Recording : {time.time()-t1:.2f}s")

    # 2. Whisper
    t2 = time.time()

    result = model.transcribe(
    filename,
    language="en",
    beam_size=5,
    best_of=5,
    fp16=False
    )

    print(f"Whisper   : {time.time()-t2:.2f}s")

    text = result["text"].strip()

    print("\nYou:", text)

    # 3. AI
    t3 = time.time()

    command = think(text)

    print(f"Qwen      : {time.time()-t3:.2f}s")

    # 4. Robot
    t4 = time.time()

    execute(command)

    print(f"Robot     : {time.time()-t4:.2f}s")