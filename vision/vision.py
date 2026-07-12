from vision.camera import get_frame
from vision.detector import detect

def get_vision_context():

    frame = get_frame()

    if frame is None:
        return "Camera unavailable."

    objects = detect(frame)

    if len(objects) == 0:
        return "Camera sees nothing."

    names = []

    for obj in objects:
        names.append(obj["name"])

    # Remove duplicates
    names = list(dict.fromkeys(names))

    return "Camera currently sees: " + ", ".join(names)