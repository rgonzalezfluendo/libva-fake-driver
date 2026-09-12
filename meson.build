project('libva-fake-driver', 'cpp',
  default_options: [
    'cpp_std=gnu++23',
    'warning_level=2',
    # fake_drv_video.so calls gbm_bo_map2(), which is exported by the companion
    # fake_gbm.so and resolved at load time (the fake GBM is LD_PRELOADed into
    # the process). Allow those runtime-resolved symbols, like the GN build.
    'b_lundef=false',
  ],
)

cc = meson.get_compiler('cpp')

# Dependencies mirror the pkg_config() templates in BUILD.gn.
libva_dep = dependency('libva', required: true)
gbm_dep = dependency('gbm', required: true)
libdrm_dep = dependency('libdrm', required: true)
dav1d_dep = dependency('dav1d', required: true)
vpx_dep = dependency('vpx', required: true)
openh264_dep = dependency('openh264', required: true)
# Not all distributions ship a pkg-config file for libyuv (e.g. Debian/Ubuntu),
# so fall back to the bare library if it cannot be found via pkg-config.
libyuv_dep = dependency('libyuv', required: false)
if not libyuv_dep.found()
  libyuv_dep = cc.find_library('yuv', required: true)
endif

codec_deps = [
  libva_dep,
  gbm_dep,
  libdrm_dep,
  dav1d_dep,
  vpx_dep,
  libyuv_dep,
  openh264_dep,
]

# Signal visibility with explicit visibility("default") annotations on the
# public entry points; see fake_drv_video.cc and fake_gbm.cc. Also match the
# Chromium/ChromiumOS exception settings from common.mk.
add_project_arguments(
  '-fvisibility=hidden',
  '-fvisibility-inlines-hidden',
  '-fno-exceptions',
  '-fno-unwind-tables',
  '-fno-asynchronous-unwind-tables',
  '-Wno-unused-parameter',
  '-Wno-missing-field-initializers',
  '-Wno-deprecated-declarations',
  '-Wno-type-limits',
  '-Wno-attributes',
  '-include',
  'gbm_compat.h',
  language: 'cpp',
)

# gbm_compat.h lives in the meson/ directory and is force-included above; make
# sure the compiler can find it.
compat_inc = include_directories('meson')

# Same source set as the "fake_libva_driver_internals" source_set in BUILD.gn.
fake_libva_driver_internals = static_library(
  'fake_libva_driver_internals',
  sources: [
    'base/scoped_fd.cc',
    'av1_decoder_delegate.cc',
    'fake_buffer.cc',
    'fake_config.cc',
    'fake_context.cc',
    'fake_driver.cc',
    'fake_image.cc',
    'fake_surface.cc',
    'h264_decoder_delegate.cc',
    'no_op_context_delegate.cc',
    'scoped_bo_mapping_factory.cc',
    'vpx_decoder_delegate.cc',
  ],
  pic: true,
  dependencies: codec_deps,
  include_directories: compat_inc,
)

# Fake GBM is a libgbm implementation for headless environments. It must stay
# under the name "fake_gbm" (no "lib" prefix), which is what its consumers
# (LD_PRELOAD, testing harnesses) expect.
fake_gbm = shared_library(
  'fake_gbm',
  'fake_gbm.cc',
  dependencies: [gbm_dep, libdrm_dep],
  name_prefix: '',
  install: true,
  install_dir: get_option('libdir'),
  include_directories: compat_inc,
)

# The libva backend. Keeps the name "fake_drv_video" (no "lib" prefix), which is
# what LIBVA_DRIVER_NAME=fake looks up as fake_drv_video.so.
fake_drv_video = shared_library(
  'fake_drv_video',
  'fake_drv_video.cc',
  link_with: fake_libva_driver_internals,
  dependencies: codec_deps,
  name_prefix: '',
  install: true,
  install_dir: get_option('libdir'),
  include_directories: compat_inc,
)