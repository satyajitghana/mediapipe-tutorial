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

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";
constexpr char kWindowName[] = "MediaPipe";

::mediapipe::Status RunGraph() {
  mediapipe::CalculatorGraphConfig config =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(R"(
        input_stream: "input_video"
        output_stream: "output_video"
        node {
          calculator: "OpenCvVideoDecoderCalculator"
          input_stream: "RAWVIDEO:input_video"
          output_stream: "DECVIDEO:output_video"
        }
      )");

  LOG(INFO) << "Initialize the calculator graph";

  mediapipe::CalculatorGraph graph;
  MP_RETURN_IF_ERROR(graph.Initialize(config));

  LOG(INFO) << "Initialize the VideoCapture";

  cv::VideoCapture capture;

  capture.open(
      "videotestsrc pattern=smpte ! "
      "video/x-raw,width=1280,height=720,format=BGR ! appsink",
      cv::CAP_GSTREAMER);

  RET_CHECK(capture.isOpened());

  LOG(INFO) << "Start running the calculator graph";

  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                   graph.AddOutputStreamPoller(kOutputStream));
  MP_RETURN_IF_ERROR(graph.StartRun({}));

  LOG(INFO) << "Start grabbing frames from capture device";
  // this is the main loop
  bool grab_frames = true;
  while (grab_frames and capture.isOpened()) {
    cv::Mat frame_raw;

    // get the current frame from capture device
    capture >> frame_raw;

    if (frame_raw.empty()) {
      LOG(WARNING) << "Empty frame, probably stream ended";
      break;
    }

    cv::Mat frame;

    cv::cvtColor(frame_raw, frame, cv::COLOR_BGR2RGB);

    // Wrap the OpenCV Mat with mediapipe ImageFrame
    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
        mediapipe::ImageFormat::SRGB, frame.cols, frame.rows,
        mediapipe::ImageFrame::kDefaultAlignmentBoundary);

    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());

    frame.copyTo(input_frame_mat);

    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

    // send this ImageFrame as a Packet to the graph
    MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us))));

    // get the result packet from the graph, or die
    mediapipe::Packet packet;

    if (not poller.Next(&packet)) break;

    auto& output_frame = packet.Get<mediapipe::ImageFrame>();

    // Convert the output ImageFrame back to OpenCV Mat to display
    cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
    cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_GRAY2BGR);

    cv::imshow(kWindowName, output_frame_mat);
    const int pressed_key = cv::waitKey(5);
    if (pressed_key >= 0 and pressed_key != 255) grab_frames = false;
  }

  LOG(INFO) << "Shutting down.";

  MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));

  return graph.WaitUntilDone();
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