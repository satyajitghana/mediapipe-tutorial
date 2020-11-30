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

Expected Console Output

```shell
shadowleaf@DESKTOP-TCFM035:~/mediapipe-tutorial/01-video-decoder$ bazel run videodecoder:videodecoder
INFO: Analyzed target //videodecoder:videodecoder (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //videodecoder:videodecoder up-to-date:
  bazel-bin/videodecoder/videodecoder
INFO: Elapsed time: 5.724s, Critical Path: 5.47s
INFO: 2 processes: 2 linux-sandbox.
INFO: Build completed successfully, 3 total actions
INFO: Build completed successfully, 3 total actions
I20201130 01:18:27.804252 24639 main.cc:31] Initialize the calculator graph
I20201130 01:18:27.804692 24639 main.cc:36] Initialize the VideoCapture
[ WARN:0] OpenCV | GStreamer warning: Cannot query video position: status=1, value=0, duration=-1
I20201130 01:18:27.823624 24639 main.cc:47] Start running the calculator graph
I20201130 01:18:27.824116 24639 main.cc:53] Start grabbing frames from capture device
I20201130 01:18:28.989396 24639 main.cc:104] Shutting down.
W20201130 01:18:28.989593 24969 videodecoder_calculator.cc:68] Closing Calculator
I20201130 01:18:28.991317 24639 main.cc:121] Success
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