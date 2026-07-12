from ultralytics import YOLO
from vision.camera import get_frame

model = YOLO("yolov8n.pt")


def describe_scene():

    frame = get_frame()

    if frame is None:
        return "Camera unavailable."

    results = model(frame, verbose=False)

    names = []

    for box in results[0].boxes:

        cls = int(box.cls[0])

        name = model.names[cls]

        if name not in names:
            names.append(name)

    if len(names)==0:
        return "Nothing detected."

    return ", ".join(names)