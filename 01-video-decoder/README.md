# Video Decoder - Mediapipe

start a udp stream server using ffmpeg

```
.\ffmpeg.exe -f dshow -framerate 30 -i video="USB2.0 HD UVC WebCam" -vcodec libx264 -r 10 -b:v 2014k -s 640x480 -ab 32k -ar 44100 -f mpegts -flush_packets 0 udp://127.0.0.1:5120?pkt_size=1316
```

or this for faster streaming

```
.\ffmpeg.exe -f dshow -i video="USB2.0 HD UVC WebCam" -vcodec libx264 -tune zerolatency -s 320x240 -f mpegts -flush_packets 0 udp://127.0.0.1:5120?pkt_size=200
```

if you need to know the video device name use

```
.\ffmpeg.exe list_devices true -f dshow -i dummy
```

## ISSUE

WSL NETWORKING IS A CLUSTERFUCK :/