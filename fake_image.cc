// Copyright 2023 The Chromium Authors
// Copyright 2024 The ChromiumOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/40285824): Remove this and convert code to safer constructs.
#pragma allow_unsafe_buffers
#endif

#include "fake_image.h"

#include "base/ptr_util.h"
#include "fake_buffer.h"
#include "fake_driver.h"

namespace libvafake {

std::unique_ptr<FakeImage> FakeImage::Create(IdType id,
                                             const VAImageFormat& format,
                                             int width,
                                             int height,
                                             FakeDriver& fake_driver,
                                             VAImage* va_image) {
  // Support the NV12 format that Chrome requests as well as the planar YUV 420
  // formats (I420/YV12) that other clients (e.g. FFmpeg) request when
  // downloading a decoded NV12 surface.
  const bool is_nv12 = format.fourcc == static_cast<uint32_t>(VA_FOURCC_NV12);
  const bool is_i420 = format.fourcc == static_cast<uint32_t>(VA_FOURCC_I420);
  const bool is_yv12 = format.fourcc == static_cast<uint32_t>(VA_FOURCC_YV12);
  CHECK(is_nv12 || is_i420 || is_yv12);

  // Validate the |format|. Clients should request VA_LSB_FIRST images only.
  CHECK_EQ(format.byte_order, static_cast<uint32_t>(VA_LSB_FIRST));
  CHECK_EQ(format.bits_per_pixel, 12u);

  std::vector<Plane> planes;
  uint32_t data_size = 0;

  // The Y plane is always first, with a stride equal to the image width.
  planes.emplace_back(/*stride=*/static_cast<uint32_t>(width),
                      /*offset=*/0);

  // TODO(b/358445928): bring back safe math.
  // Y plane size = width * height.
  const uint32_t y_size = static_cast<uint32_t>(width) *
                          static_cast<uint32_t>(height);

  if (is_nv12) {
    // UV stride = ceil(width / 2) * 2.
    uint32_t uv_stride = static_cast<uint32_t>(width);
    uv_stride += 1;
    uv_stride /= 2;
    uv_stride *= 2;

    // UV plane size = ceil(height / 2) * UV stride.
    uint32_t uv_size = static_cast<uint32_t>(height);
    uv_size += 1;
    uv_size /= 2;
    uv_size *= uv_stride;

    planes.emplace_back(/*stride=*/uv_stride, /*offset=*/y_size);
    data_size = y_size + uv_size;
  } else {
    // Chroma planes are half-width and half-height (ceil-rounded).
    const uint32_t chroma_stride = (static_cast<uint32_t>(width) + 1u) / 2u;
    const uint32_t chroma_height = (static_cast<uint32_t>(height) + 1u) / 2u;
    const uint32_t chroma_size = chroma_stride * chroma_height;

    // I420 stores U before V; YV12 stores V before U.
    const uint32_t first_chroma_offset = y_size;
    const uint32_t second_chroma_offset = y_size + chroma_size;

    planes.emplace_back(
        /*stride=*/chroma_stride,
        /*offset=*/is_i420 ? first_chroma_offset : second_chroma_offset);
    planes.emplace_back(
        /*stride=*/chroma_stride,
        /*offset=*/is_i420 ? second_chroma_offset : first_chroma_offset);
    data_size = y_size + 2u * chroma_size;
  }

  memset(va_image, 0, sizeof(VAImage));
  va_image->image_id = id;
  va_image->format = format;

  FakeBuffer::IdType buf = fake_driver.CreateBuffer(
      /*context=*/VA_INVALID_ID, VAImageBufferType,
      /*size_per_element=*/1, data_size, /*data=*/nullptr);
  va_image->buf = buf;

  va_image->width = static_cast<uint16_t>(width);
  va_image->height = static_cast<uint16_t>(height);
  va_image->data_size = data_size;
  va_image->num_planes = static_cast<uint32_t>(planes.size());
  for (size_t i = 0; i < planes.size(); ++i) {
    va_image->pitches[i] = planes[i].stride;
    va_image->offsets[i] = planes[i].offset;
  }

  return base::WrapUnique(
      new FakeImage(id, format, width, height, std::move(planes),
                    fake_driver.GetBuffer(buf), fake_driver));
}

FakeImage::FakeImage(FakeImage::IdType id,
                     const VAImageFormat& format,
                     int width,
                     int height,
                     std::vector<Plane> planes,
                     const FakeBuffer& buffer,
                     FakeDriver& driver)
    : id_(id),
      format_(format),
      width_(width),
      height_(height),
      planes_(std::move(planes)),
      buffer_(buffer),
      driver_(driver) {}

FakeImage::~FakeImage() {
  driver_.DestroyBuffer(buffer_.GetID());
}

FakeImage::IdType FakeImage::GetID() const {
  return id_;
}

const VAImageFormat& FakeImage::GetFormat() const {
  return format_;
}

int FakeImage::GetWidth() const {
  return width_;
}

int FakeImage::GetHeight() const {
  return height_;
}

const FakeBuffer& FakeImage::GetBuffer() const {
  return buffer_;
}

uint32_t FakeImage::GetPlaneStride(size_t plane) const {
  CHECK_LT(plane, planes_.size());
  return planes_[plane].stride;
}

uint32_t FakeImage::GetPlaneOffset(size_t plane) const {
  CHECK_LT(plane, planes_.size());
  return planes_[plane].offset;
}

FakeImage::Plane::Plane(uint32_t stride, uint32_t offset)
    : stride(stride), offset(offset) {}

}  // namespace libvafake
