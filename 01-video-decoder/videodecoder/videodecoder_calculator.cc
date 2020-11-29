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
class OpenCvVideoDecoderCalculator : public CalculatorBase {
 public:
  static ::mediapipe::Status GetContract(CalculatorContract* cc) {}

  ::mediapipe::Status Open(CalculatorContext* cc) override {}

  ::mediapipe::Status Process(CalculatorContext* cc) override {}

  ::mediapipe::Status Close(CalculatorContext* cc) override {}

 private:
  int width_;
  int height_;
  int frame_count_;
  Timestamp prev_timestamp_ = Timestamp::Unset();
};

REGISTER_CALCULATOR(OpenCvVideoDecoderCalculator);

}  // namespace mediapipe