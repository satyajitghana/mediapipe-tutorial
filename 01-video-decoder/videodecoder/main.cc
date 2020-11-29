#include <cstdlib>
#include <iostream>

#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/commandlineflags.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"

DEFINE_string(
    calculator_graph_config_file, "",
    "Name of the file containing  text format CalculatorGraphConfig proto.");

::mediapipe::Status RunGraph() {
  mediapipe::CalculatorGraph graph;

  cv::VideoCapture capture;

  capture.open(
      "videotestsrc pattern=smpte ! "
      "video/x-raw,width=1280,height=720,format=BGR ! appsink",
      cv::CAP_GSTREAMER);

  if (not capture.isOpened()) {
    std::cout << "Failed to open Capture" << std::endl;
  }

  cv::Mat frame;

  for (;;) {
    capture.read(frame);

    if (frame.empty()) {
      std::cerr << "ERROR ! empty frame";
      break;
    }

    cv::imshow("frames", frame);

    if (cv::waitKey(5) >= 0) break;
  }
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  ::mediapipe::Status run_status = RunGraph();

  if (not run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success";
  }

  return EXIT_SUCCESS;
}