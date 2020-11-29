import cv2
import subprocess

# stream_host = (
#     subprocess.Popen(
#         "cat /etc/resolv.conf | grep nameserver | awk '{print $2}'",
#         shell=True,
#         stdout=subprocess.PIPE,
#         stderr=subprocess.STDOUT,
#     )
#     .communicate()[0]
#     .strip()
# ).decode("utf-8")

# stream_url = f"udp://{stream_host}:5120"

cap = cv2.VideoCapture(
    "videotestsrc pattern=snow ! video/x-raw,width=1280,height=720,format=BGR ! appsink",
    cv2.CAP_GSTREAMER,
)

while cap.isOpened():
    ret, frame = cap.read()

    print(ret)

    if ret:
        cv2.namedWindow("image", cv2.WINDOW_NORMAL)
        cv2.imshow("frame", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
