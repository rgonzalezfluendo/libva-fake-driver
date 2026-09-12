# VA-API fake backend for libva

VA-API is an API for video/image decoding/encoding acceleration implemented by
[libva] ([x11-libs/libva]). `libva-fake-driver` provides a fake backend for it
for VMs and other test-related images.

It can be explicitly exercised by running e.g.:

    LIBVA_DRIVER_NAME="fake" vainfo

wherever it might be installed. See https://tinyurl.com/libva-fake-driver for
more information.

# Building with Meson

Requires libva, gbm, libdrm and the codec development libraries (dav1d, vpx,
libyuv, openh264). Install them with your distribution's package manager, then:

    meson setup build
    ninja -C build
    meson install -C build     # optionally, with DESTDIR for staging

This produces two shared objects named `fake_gbm.so` and `fake_drv_video.so`
(with no `lib` prefix) in the build directory or the configured `libdir`.

# Usage

The driver is split into two shared objects: `fake_gbm.so` (a GBM + libdrm
replacement exporting `gbm_bo_map2`) and `fake_drv_video.so` (the libva
driver). `fake_drv_video.so` needs `gbm_bo_map2` at `dlopen()` time, so the
fake GBM library must be preloaded or resolvable:

    LIBVA_DRIVER_NAME="fake" LD_PRELOAD=/path/to/fake_gbm.so vainfo

For H.264 decode with FFmpeg, surfaces are allocated by the client with
VA-allocated memory instead of a DRM PRIME buffer. The driver backs those
surfaces internally, so the real decoder is used and decoded frames are
correct:

    LIBVA_DRIVER_NAME="fake" \
    LD_PRELOAD=/path/to/fake_gbm.so \
    ffmpeg -hwaccel vaapi -hwaccel_device /dev/dri/renderD128 \
           -c:v h264 -i input.h264 -f null -

Set `USE_NO_OP_CONTEXT_DELEGATE=1` to force the no-op context delegate instead
of running the real decoder (useful for quickly exercising the VA-API plumbing
without decoding).

[libva]: https://github.com/intel/libva
[x11-libs/libva]: https://chromium.googlesource.com/chromiumos/overlays/chromiumos-overlay/+/refs/heads/master/x11-libs/libva/
