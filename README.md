# Mediapipe Tutorial

## WSL2 setup

Install OpenCV and Bazel

```
sudo ./setup-env-wsl2.sh
```

Setup OpenCV and modify WORKSPACE file to point to opencv installation

```
sudo ./mediapipe/setup_opencv.sh
```

If you are building for android then run

This will also modify the WORKSPACE file and point to the right install location of android sdk and ndk

```
sudo ./mediapipe/setup_android_sdk_and_ndk.sh
```

Install requirements

```
pip3 install mediapipe/requirements.txt
```

## Notes

bazel needs an alias a to work in wsl after its install procedure, or you can use `ln` to link it

```
alias bazel='/usr/local/bazel/3.4.0/lib/bazel/bin/bazel'
```
