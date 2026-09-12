// Copyright 2026 The ChromiumOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// libva-fake-driver targets the ChromiumOS minigbm GBM API, which extends the
// upstream (Mesa) gbm.h with a few extra macros and entry points. The upstream
// libgbm headers shipped by common distributions (e.g. Debian and Ubuntu) do
// not provide them, so we only define the extensions that are missing.
//
// This header is force-included (-include) by the Meson build; it must stay
// build-time only and must not change the behavior of the driver.

#ifndef LIBVA_FAKE_DRIVER_GBM_COMPAT_H_
#define LIBVA_FAKE_DRIVER_GBM_COMPAT_H_

#include <gbm.h>

// Ensure the standard headers used by the sources are available: some
// translation units rely on them being transitively included (e.g. memcpy() in
// fake_buffer.cc and std::find_if in object_tracker.h / fake_drv_video.cc).
#include <algorithm>
#include <cstring>

// ChromiumOS minigbm (src/gbm.h) defines these in addition to the upstream
// headers.
#ifndef GBM_FORMAT_P010
#define GBM_FORMAT_P010 0x30313050
#endif

#ifndef GBM_BO_IMPORT_FD_PLANAR
#define GBM_BO_IMPORT_FD_PLANAR 0x5505
#endif

#ifndef GBM_BO_USE_SW_READ_OFTEN
#define GBM_BO_USE_SW_READ_OFTEN (1 << 6)
#endif

#ifndef GBM_BO_USE_SW_WRITE_OFTEN
#define GBM_BO_USE_SW_WRITE_OFTEN (1 << 7)
#endif

// gbm_bo_map2() is a minigbm-only extension. Declare it so the rest of the
// code can call it; the implementation lives in fake_gbm.cc.
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBVA_FAKE_DRIVER_HAVE_GBM_BO_MAP2
void *gbm_bo_map2(struct gbm_bo *bo,
                  uint32_t x,
                  uint32_t y,
                  uint32_t width,
                  uint32_t height,
                  uint32_t transfer_flags,
                  uint32_t *stride,
                  void **map_data,
                  int plane);
#endif

#ifdef __cplusplus
}
#endif

#endif  // LIBVA_FAKE_DRIVER_GBM_COMPAT_H_