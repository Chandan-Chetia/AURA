import cv2
from ultralytics import YOLO
import threading

model = YOLO("yolov8n.pt")

cap = cv2.VideoCapture(0)

def run_camera():

    while True:

        ret, frame = cap.read()

        if not ret:
            continue

        results = model(frame, verbose=False)

        annotated = results[0].plot()

        cv2.imshow("Robot Vision", annotated)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()


def start_camera():

    thread = threading.Thread(
        target=run_camera,
        daemon=True
    )

    thread.start()