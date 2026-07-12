import cv2

camera = cv2.VideoCapture(0)

if not camera.isOpened():
    raise RuntimeError("Camera not found")


def get_frame():
    ok, frame = camera.read()

    if not ok:
        return None

    return frame