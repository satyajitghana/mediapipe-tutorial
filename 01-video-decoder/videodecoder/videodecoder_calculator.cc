#include <stdio.h>

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_format.pb.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/video_stream_header.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/tool/status_util.h"

namespace mediapipe {

namespace videodecoder {

namespace {
constexpr char kVideoInputTag[] = "RAWVIDEO";
constexpr char kVideoOutputTag[] = "DECVIDEO";
}  // namespace

class OpenCvVideoDecoderCalculator : public CalculatorBase {
 public:
  static mediapipe::Status GetContract(CalculatorContract* cc);
  mediapipe::Status Open(CalculatorContext* cc) override;
  mediapipe::Status Process(CalculatorContext* cc) override;
  mediapipe::Status Close(CalculatorContext* cc) override;
};

REGISTER_CALCULATOR(OpenCvVideoDecoderCalculator);

::mediapipe::Status OpenCvVideoDecoderCalculator::GetContract(
    mediapipe::CalculatorContract* cc) {
  cc->Inputs().Tag(kVideoInputTag).Set<ImageFrame>();
  cc->Outputs().Tag(kVideoOutputTag).Set<ImageFrame>();

  return ::mediapipe::OkStatus();
}

::mediapipe::Status OpenCvVideoDecoderCalculator::Open(CalculatorContext* cc) {
  return ::mediapipe::OkStatus();
};

::mediapipe::Status OpenCvVideoDecoderCalculator::Process(
    CalculatorContext* cc) {
  auto& frame = cc->Inputs().Tag(kVideoInputTag).Get<ImageFrame>();

  cv::Mat mat = formats::MatView(&frame);

  // convert RGB to GRAY
  cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

  // flip the video upside down
  cv::flip(mat, mat, 0);

  auto output =
      absl::make_unique<ImageFrame>(ImageFormat::GRAY8, mat.cols, mat.rows,
                                    ImageFrame::kDefaultAlignmentBoundary);

  cv::Mat output_mat = mediapipe::formats::MatView(output.get());

  mat.copyTo(output_mat);

  cc->Outputs()
      .Tag(kVideoOutputTag)
      .Add(output.release(), cc->InputTimestamp());

  return ::mediapipe::OkStatus();
};

::mediapipe::Status OpenCvVideoDecoderCalculator::Close(CalculatorContext* cc) {
  LOG(WARNING) << "Closing Calculator";

  return ::mediapipe::OkStatus();
};

}  // namespace videodecoder
}  // namespace mediapipe