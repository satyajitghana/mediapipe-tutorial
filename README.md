# Mediapipe Tutorial

## WSL2 setup

Install OpenCV and Bazel

```shell
$ sudo ./setup-env-wsl2.sh
```

Setup OpenCV and modify WORKSPACE file to point to opencv installation

```shell
$ sudo ./mediapipe/setup_opencv.sh
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
