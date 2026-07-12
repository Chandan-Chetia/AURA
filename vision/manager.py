from .camera import get_frame
from .detector import detect


def get_scene():

    frame = get_frame()

    if frame is None:
        return []

    return detect(frame)