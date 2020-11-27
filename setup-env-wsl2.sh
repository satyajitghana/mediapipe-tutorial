#!/bin/bash

sudo apt-get update && sudo apt-get install -y build-essential git python zip adb openjdk-8-jdk

curl -sLO --retry 5 --retry-max-time 10 \
https://storage.googleapis.com/bazel/3.4.0/release/bazel-3.4.0-installer-linux-x86_64.sh && \
sudo mkdir -p /usr/local/bazel/3.4.0 && \
chmod 755 bazel-3.4.0-installer-linux-x86_64.sh && \
sudo ./bazel-3.4.0-installer-linux-x86_64.sh --prefix=/usr/local/bazel/3.4.0 && \
source /usr/local/bazel/3.4.0/lib/bazel/bin/bazel-complete.bash

bazel run --define MEDIAPIPE_DISABLE_GPU=1 \
    mediapipe/examples/desktop/hello_world:hello_world && \
alias bazel='/usr/local/bazel/3.4.0/lib/bazel/bin/bazel'

sudo apt-get install -y libopencv-core-dev libopencv-highgui-dev \
                       libopencv-calib3d-dev libopencv-features2d-dev \
                       libopencv-imgproc-dev libopencv-video-dev
