# Video Decoder - Mediapipe

Make sure OpenCV is built with GStreamer, since we will be using it to generate the test video

## Build

```shell
bazel build videodecoder:videodecoder
```

## Run

```shell
export GLOG_logtostderr=1
bazel run videodecoder:videodecoder
```

You'll see a Gray-Flipped test video screen

The original gstreamer test video can be viewed by

```shell
gst-launch-1.0 -v videotestsrc pattern=smpte ! video/x-raw,width=1280,height=720 ! autovideosink
```

## Some notes, which can be used to stream ffmpeg video stream via the network to the videodecoder mediapipe app

start a udp stream server using ffmpeg

```shell
.\ffmpeg.exe -f dshow -framerate 30 -i video="USB2.0 HD UVC WebCam" -vcodec libx264 -r 10 -b:v 2014k -s 640x480 -ab 32k -ar 44100 -f mpegts -flush_packets 0 udp://127.0.0.1:5120?pkt_size=1316
```

or this for faster streaming

```shell
.\ffmpeg.exe -f dshow -i video="USB2.0 HD UVC WebCam" -vcodec libx264 -tune zerolatency -s 320x240 -f mpegts -flush_packets 0 udp://127.0.0.1:5120?pkt_size=200
```

if you need to know the video device name use

```shell
.\ffmpeg.exe list_devices true -f dshow -i dummy
```

## ISSUE

WSL NETWORKING IS A CLUSTERFUCK :/