```
LD_PRELOAD=`realpath builddir/fake_gbm.so` LD_LIBRARY_PRELOAD=`realpath builddir` LIBVA_DRIVER_NAME=fake LIBVA_DRIVERS_PATH=`realpath builddir` vainfo
Trying display: wayland
libva info: VA-API version 1.24.0
libva info: User environment variable requested driver 'fake'
libva info: Trying to open /tmp/deepseek/libva-fake-driver/builddir/fake_drv_video.so
libva info: Found init function __vaDriverInit_1_0
libva info: va_openDriver() returns 0
vainfo: VA-API version: 1.24 (libva 2.24.0)
vainfo: Driver version: Chromium fake libva driver
vainfo: Supported profile and entrypoints
      VAProfileNone                   : VAEntrypointVideoProc
      VAProfileH264Main               : VAEntrypointVLD
      VAProfileH264Main               : VAEntrypointEncSlice
      VAProfileH264High               : VAEntrypointVLD
      VAProfileH264High               : VAEntrypointEncSlice
      VAProfileJPEGBaseline           : VAEntrypointVLD
      VAProfileJPEGBaseline           : VAEntrypointEncPicture
      VAProfileH264ConstrainedBaseline: VAEntrypointVLD
      VAProfileH264ConstrainedBaseline: VAEntrypointEncSlice
      VAProfileVP8Version0_3          : VAEntrypointVLD
      VAProfileVP8Version0_3          : VAEntrypointEncSlice
      VAProfileVP9Profile0            : VAEntrypointVLD
      VAProfileVP9Profile0            : VAEntrypointEncSlice
      VAProfileVP9Profile2            : VAEntrypointVLD
      VAProfileVP9Profile2            : VAEntrypointEncSlice
      VAProfileAV1Profile0            : VAEntrypointVLD
```


```
GST_REGISTRY=/tmp/caca GST_DEBUG="*va*:7" LD_PRELOAD=`realpath builddir/fake_gbm.so` LD_LIBRARY_PRELOAD=`realpath builddir` LIBVA_DRIVER_NAME=fake LIBVA_DRIVERS_PATH=`realpath builddir`  gst-inspect-1.0 va
0:00:00.021886740     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: VA-API version 1.24.0
0:00:00.021932578     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: User environment variable requested driver 'fake'
0:00:00.021941635     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: Trying to open /tmp/deepseek/libva-fake-driver/builddir/fake_drv_video.so
0:00:00.024057855     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: Found init function __vaDriverInit_1_0
0:00:00.024079617     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: va_openDriver() returns 0
0:00:00.024085969     663679     663679 INFO                   vaapi gstvaapiutils.c:122:vaapi_initialize: VA-API version 1.24
0:00:00.024295490     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: VA-API version 1.24.0
0:00:00.024307593     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: User environment variable requested driver 'fake'
0:00:00.024314437     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: Trying to open /tmp/deepseek/libva-fake-driver/builddir/fake_drv_video.so
0:00:00.024334124     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: Found init function __vaDriverInit_1_0
0:00:00.024345626     663679     663679 INFO                   vaapi gstvaapiutils.c:95:gst_vaapi_log: va_openDriver() returns 0
0:00:00.024353030     663679     663679 INFO                   vaapi gstvaapiutils.c:122:vaapi_initialize: VA-API version 1.24
0:00:00.024361447     663679     663679 INFO            vaapidisplay gstvaapidisplay.c:983:gst_vaapi_display_create:<vaapidisplaydrm0> new display addr=0x559b300424c0
0:00:00.024375934     663679     663679 INFO            vaapidisplay gstvaapidisplay.c:795:ensure_vendor_string:<vaapidisplaydrm0> vendor: Chromium fake libva driver
0:00:00.024389731     663679     663679 INFO            vaapidisplay gstvaapidisplay.c:834:set_driver_quirks:<vaapidisplaydrm0> Matched driver string "Chromium fake libva driver", setting quirks (0)
0:00:00.024404339     663679     663679 DEBUG           vaapidisplay gstvaapidisplay.c:711:ensure_image_formats: 1 image formats
0:00:00.024417905     663679     663679 DEBUG           vaapidisplay gstvaapidisplay.c:713:ensure_image_formats:   NV12
0:00:00.934812152     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-1 in (null)
0:00:00.934836318     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-2 in (null)
0:00:00.934840797     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-3 in (null)
0:00:00.934844063     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-4 in (null)
0:00:00.934847149     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-5 in (null)
0:00:00.934879060     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-DP-6 in (null)
0:00:00.934885853     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-HDMI-A-1 in (null)
0:00:00.934893828     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-Writeback-1 in (null)
0:00:00.934898678     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1-eDP-1 in (null)
0:00:00.934903327     663679     663679 LOG                       va gstvadevice_linux.c:97:gst_va_device_find_devices: Ignoring card1 in /dev/dri/card1
0:00:00.935108048     663679     663679 INFO               vadisplay gstvadisplay_drm.c:157:gst_va_display_drm_create_va_display:<vadisplaydrm0> DRM render node with kernel driver amdgpu
0:00:00.935149017     663679     663679 INFO               vadisplay gstvadisplay.c:353:_va_info:<vadisplaydrm0> VA info: VA-API version 1.24.0
0:00:00.935158214     663679     663679 INFO               vadisplay gstvadisplay.c:353:_va_info:<vadisplaydrm0> VA info: User environment variable requested driver 'fake'
0:00:00.935165438     663679     663679 INFO               vadisplay gstvadisplay.c:353:_va_info:<vadisplaydrm0> VA info: Trying to open /tmp/deepseek/libva-fake-driver/builddir/fake_drv_video.so
0:00:00.935182120     663679     663679 INFO               vadisplay gstvadisplay.c:353:_va_info:<vadisplaydrm0> VA info: Found init function __vaDriverInit_1_0
0:00:00.935195426     663679     663679 INFO               vadisplay gstvadisplay.c:353:_va_info:<vadisplaydrm0> VA info: va_openDriver() returns 0
0:00:00.935199944     663679     663679 INFO               vadisplay gstvadisplay.c:405:gst_va_display_initialize:<vadisplaydrm0> VA-API version 1.24
0:00:00.935206066     663679     663679 INFO               vadisplay gstvadisplay.c:176:_gst_va_display_filter_driver: VA-API driver vendor: Chromium fake libva driver
0:00:00.935211176     663679     663679 WARN               vadisplay gstvadisplay.c:186:_gst_va_display_filter_driver:<vadisplaydrm0> Unsupported driver: Chromium fake libva driver
Plugin Details:
  Name                     va
  Description              VA-API codecs plugin
  Filename                 /usr/lib/gstreamer-1.0/libgstva.so
  Version                  1.28.6
  License                  LGPL
  Source module            gst-plugins-bad
  Documentation            https://gstreamer.freedesktop.org/documentation/va/
  Source release date      2026-08-05
  Binary package           Arch Linux GStreamer 1.28.6-3
  Origin URL               https://www.archlinux.org/
```

```
LD_PRELOAD=`realpath builddir/fake_gbm.so` LD_LIBRARY_PRELOAD=`realpath builddir` LIBVA_DRIVER_NAME=fake LIBVA_DRIVERS_PATH=`realpath builddir`  fluster --no-emoji list -c -d H.264


List of available test suites:

JVT-MVC
    Codec: H.264
    Description: JVT Multiview Video Coding test suite
    Test vectors: 20

JVT-Professional_profiles
    Codec: H.264
    Description: JVT Professional Profiles test suite
    Test vectors: 38

JVT-AVC_V1
    Codec: H.264
    Description: JVT Advanced Video Coding v1 test suite
    Test vectors: 135

JVT-FR-EXT
    Codec: H.264
    Description: JVT Fidelity Range Extension test suite
    Test vectors: 69

JVT-SVC
    Codec: H.264
    Description: JVT Scalable Video Coding test suite
    Test vectors: 185

List of available decoders:

H.264
    Chromium-H.264: Chromium H.264 decoder for Chromium... KO
    FFmpeg-H.264: FFmpeg H.264 SW decoder... OK
    FFmpeg-H.264-CUDA: FFmpeg H.264 CUDA decoder... OK
    FFmpeg-H.264-D3D11VA: FFmpeg H.264 D3D11VA decoder... KO
    FFmpeg-H.264-DXVA2: FFmpeg H.264 DXVA2 decoder... KO
    FFmpeg-H.264-QSV: FFmpeg H.264 QSV decoder... OK
    FFmpeg-H.264-VAAPI: FFmpeg H.264 VAAPI decoder... OK
    FFmpeg-H.264-VDPAU: FFmpeg H.264 VDPAU decoder... OK
    FFmpeg-H.264-Vulkan: FFmpeg H.264 Vulkan decoder... OK
    FFmpeg-H.264-v4l2m2m: FFmpeg H.264 v4l2m2m decoder... OK
    Fluendo-H.264-DXVA2: Fluendo H.264 DXVA2 decoder for GStreamer... KO
    Fluendo-H.264-HW-lcevchwvah264dec: Fluendo H.264 HW decoder for GStreamer... KO
    Fluendo-H.264-SW: Fluendo H.264 SW decoder for GStreamer... KO
    Fluendo-H.264-VAAPI: Fluendo H.264 VAAPI decoder for GStreamer... KO
    Fluendo-H.264-VDA: Fluendo H.264 VDA decoder for GStreamer... KO
    Fluendo-H.264-VDPAU: Fluendo H.264 VDPAU decoder for GStreamer... KO
    Fluendo-H.264-VT: Fluendo H.264 VT decoder for GStreamer... KO
    GStreamer-H.264-D3D11: GStreamer H.264 D3D11 decoder for GStreamer... KO
    GStreamer-H.264-D3D12: GStreamer H.264 D3D12 decoder for GStreamer... KO
    GStreamer-H.264-Libav: GStreamer H.264 Libav decoder for GStreamer... OK
    GStreamer-H.264-MSDK: GStreamer H.264 MSDK decoder for GStreamer... KO
    GStreamer-H.264-NVDEC: GStreamer H.264 NVDEC decoder for GStreamer... KO
    GStreamer-H.264-NVDECSL: GStreamer H.264 NVDECSL decoder for GStreamer... KO
    GStreamer-H.264-OpenH264: GStreamer H.264 OpenH264 decoder for GStreamer... OK
    GStreamer-H.264-QSV: GStreamer H.264 QSV decoder for GStreamer... KO
    GStreamer-H.264-V4L2: GStreamer H.264 V4L2 decoder for GStreamer... KO
    GStreamer-H.264-V4L2SL: GStreamer H.264 V4L2SL decoder for GStreamer... KO
    GStreamer-H.264-VA: GStreamer H.264 VA decoder for GStreamer... KO
    GStreamer-H.264-VAAPI: GStreamer H.264 VAAPI decoder for GStreamer... KO
    GStreamer-H.264-Vulkan: GStreamer H.264 Vulkan decoder for GStreamer... OK
    JCT-VT-H.264: JCT-VT H.264/AVC reference decoder... KO
    VKVS-H.264: Vulkan Video Samples H.264 decoder... KO
    ccdec-H.264: H.264 cros-codecs decoder... KO
```


```
LD_PRELOAD=`realpath builddir/fake_gbm.so` LD_LIBRARY_PRELOAD=`realpath builddir` LIBVA_DRIVER_NAME=fake LIBVA_DRIVERS_PATH=`realpath builddir`  fluster run -d GStreamer-H.264-VA -ts JVT-AVC_V1 -j 1 -s
```
