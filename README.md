# Mediapipe Tutorial

## WSL2 setup

Install OpenCV and Bazel

```shell
$ sudo ./setup-env-wsl2.sh
```

Install GStreamer

```shell
sudo apt install -y libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
```

```shell
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
```

Setup OpenCV and modify WORKSPACE file to point to opencv installation

Add this line in cmake command of setup_opencv.sh to build with gstreamer support
```
-DWITH_GSTREAMER=ON
```

```shell
$ sudo ./mediapipe/setup_opencv.sh
```

Install OpenGL

```shell
$ sudo apt-get install mesa-common-dev libegl1-mesa-dev libgles2-mesa-dev
$ sudo apt-get install mesa-utils
```

If you are building for android then run

This will also modify the WORKSPACE file and point to the right install location of android sdk and ndk

```shell
$ sudo ./mediapipe/setup_android_sdk_and_ndk.sh
```

Install requirements

```shell
$ pip3 install mediapipe/requirements.txt
```

## Style Guide

use clang-format

```shell
$ clang-format -style=google -dump-config > .clang-format
```

## Build



## Notes

bazel needs an alias a to work in wsl after its install procedure, or you can use `ln` to link it

```shell
alias bazel='/usr/local/bazel/3.4.0/lib/bazel/bin/bazel'
```
