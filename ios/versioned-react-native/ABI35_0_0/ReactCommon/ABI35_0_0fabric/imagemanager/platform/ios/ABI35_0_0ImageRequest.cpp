/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI35_0_0ImageRequest.h"

namespace facebook {
namespace ReactABI35_0_0 {

class ImageRequest::ImageNoLongerNeededException : public std::logic_error {
 public:
  ImageNoLongerNeededException()
      : std::logic_error("Image no longer needed.") {}
};

ImageRequest::ImageRequest(const ImageSource &imageSource)
    : imageSource_(imageSource) {
  coordinator_ = std::make_shared<ImageResponseObserverCoordinator>();
}

ImageRequest::ImageRequest(ImageRequest &&other) noexcept
    : imageSource_(std::move(other.imageSource_)),
      coordinator_(std::move(other.coordinator_)) {
  other.moved_ = true;
  other.coordinator_ = nullptr;
  other.cancelRequest_ = nullptr;
}

ImageRequest::~ImageRequest() {
  if (cancelRequest_) {
    cancelRequest_();
  }
}

void ImageRequest::setCancelationFunction(
    std::function<void(void)> cancelationFunction) {
  cancelRequest_ = cancelationFunction;
}

const ImageResponseObserverCoordinator *ImageRequest::getObserverCoordinator()
    const {
  return coordinator_.get();
}

} // namespace ReactABI35_0_0
} // namespace facebook