# Copyright 2020 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

PC_DEPS = libva
PC_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(PC_DEPS))
PC_LIBS := $(shell $(PKG_CONFIG) --libs $(PC_DEPS))

CFLAGS += -Wall -fPIC -I$(OUT)
LDFLAGS += -shared
LDLIBS += $(PC_LIBS)

LIBDIR ?= /usr/lib64/va/drivers

LIBLIBVAFAKEDRIVER := fake_drv_video.so

CC_LIBRARY($(LIBLIBVAFAKEDRIVER)): $(C_OBJECTS)

all: CC_LIBRARY($(LIBLIBVAFAKEDRIVER))

install: all
	mkdir -p $(DESTDIR)/$(LIBDIR)
	install -D -m 755 $(OUT)/$(LIBLIBVAFAKEDRIVER) $(DESTDIR)/$(LIBDIR)
