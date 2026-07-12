import cv2

from camera import get_frame
from detector import detect

while True:

    frame = get_frame()

    if frame is None:
        break

    objects = detect(frame)

    for obj in objects:

        x1, y1, x2, y2 = obj["box"]

        cv2.rectangle(frame, (x1, y1), (x2, y2), (0,255,0), 2)

        cv2.putText(
            frame,
            obj["name"],
            (x1, y1-10),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.6,
            (0,255,0),
            2
        )

    cv2.imshow("Robot Vision", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()