// Copyright (c) the JPEG XL Project Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef LIB_JXL_ENC_EXTERNAL_IMAGE_H_
#define LIB_JXL_ENC_EXTERNAL_IMAGE_H_

// Interleaved image for color transforms and Codec.

#include <stddef.h>
#include <stdint.h>

#include "jxl/types.h"
#include "lib/jxl/base/data_parallel.h"
#include "lib/jxl/base/padded_bytes.h"
#include "lib/jxl/base/status.h"
#include "lib/jxl/codec_in_out.h"
#include "lib/jxl/color_encoding_internal.h"
#include "lib/jxl/image.h"
#include "lib/jxl/image_bundle.h"

namespace jxl {
Status ConvertFromExternal(Span<const uint8_t> bytes, size_t xsize,
                           size_t ysize, size_t bits_per_sample,
                           JxlEndianness endianness, ThreadPool* pool,
                           ImageF* channel, bool float_in, size_t align);

// Convert an interleaved pixel buffer to the internal ImageBundle
// representation. This is the opposite of ConvertToExternal().
Status ConvertFromExternal(Span<const uint8_t> bytes, size_t xsize,
                           size_t ysize, const ColorEncoding& c_current,
                           bool has_alpha, bool alpha_is_premultiplied,
                           size_t bits_per_sample, JxlEndianness endianness,
                           bool flipped_y, ThreadPool* pool, ImageBundle* ib,
                           bool float_in, size_t align);
Status BufferToImageF(const JxlPixelFormat& pixel_format, size_t xsize,
                      size_t ysize, const void* buffer, size_t size,
                      ThreadPool* pool, ImageF* channel);
Status BufferToImageBundle(const JxlPixelFormat& pixel_format, uint32_t xsize,
                           uint32_t ysize, const void* buffer, size_t size,
                           jxl::ThreadPool* pool,
                           const jxl::ColorEncoding& c_current,
                           jxl::ImageBundle* ib);

}  // namespace jxl

#endif  // LIB_JXL_ENC_EXTERNAL_IMAGE_H_
