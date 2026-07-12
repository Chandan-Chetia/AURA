import sounddevice as sd
import soundfile as sf
import numpy as np
import queue

SAMPLE_RATE = 16000
CHANNELS = 1
dtype = "float32"

q = queue.Queue()


def callback(indata, frames, time, status):
    q.put(indata.copy())


def record_audio():

    print("\n🎤 Listening... (start speaking)")

    recording = []

    silence_chunks = 0
    started = False

    threshold = 0.015          # microphone sensitivity
    silence_limit = 25         # about 0.8 second silence

    with sd.InputStream(
        samplerate=SAMPLE_RATE,
        channels=CHANNELS,
        blocksize=512,
        callback=callback
    ):

        while True:

            data = q.get()

            volume = np.abs(data).mean()

            if volume > threshold:

                started = True
                silence_chunks = 0
                recording.append(data)

            elif started:

                recording.append(data)
                silence_chunks += 1

                if silence_chunks > silence_limit:
                    break

    audio = np.concatenate(recording)

    filename = "temp.wav"

    sf.write(filename, audio, SAMPLE_RATE)

    print("✅ Speech captured.")

    return filename