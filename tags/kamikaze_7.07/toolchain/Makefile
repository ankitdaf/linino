# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Main makefile for the toolchain
#
include $(TOPDIR)/rules.mk

TARGETS-y:=kernel-headers
TARGETS-$(CONFIG_GDB) += gdb
ifeq ($(CONFIG_NATIVE_TOOLCHAIN),)
  TARGETS-y+=binutils gcc uClibc
endif

TARGETS_DOWNLOAD:=$(patsubst %,%-download,$(TARGETS-y))
TARGETS_PREPARE:=$(patsubst %,%-prepare,$(TARGETS-y))
TARGETS_COMPILE:=$(patsubst %,%-compile,$(TARGETS-y))
TARGETS_INSTALL:=$(patsubst %,%-install,$(TARGETS-y))
TARGETS_CLEAN:=$(patsubst %,%-clean,$(TARGETS-y))
STAMP:=$(STAGING_DIR)/stampfiles/.toolchain_installed

all: install
download: $(TARGETS_DOWNLOAD)
compile: $(TARGETS_COMPILE)
install: $(STAMP) 
clean: $(TARGETS_CLEAN)

ifneq ($(shell $(SCRIPT_DIR)/timestamp.pl -p . $(STAMP)),$(STAMP))
  $(STAMP): $(TARGETS_INSTALL)
endif

uClibc-prepare: kernel-headers-prepare
ifeq ($(CONFIG_NATIVE_TOOLCHAIN),)
  binutils-prepare: uClibc-prepare
  gcc-prepare: binutils-install
  uClibc-compile: gcc-compile
endif
gcc-install: uClibc-install

$(STAMP):
	mkdir -p $(shell dirname $@)
	touch $@

$(STAGING_DIR)/$(REAL_GNU_TARGET_NAME):
	@mkdir -p $@
	@ln -sf ../lib $@/lib

$(TOOLCHAIN_BUILD_DIR):
	@mkdir -p $@

%-prereq %-download %-clean %-refresh %-update: FORCE
	$(MAKE) -C $* $(patsubst $*-%,%,$@)

%-prepare: $(STAGING_DIR)/$(REAL_GNU_TARGET_NAME) $(TOOLCHAIN_BUILD_DIR)	
	$(MAKE) -C $* $(patsubst $*-%,%,$@)

%-compile: %-prepare FORCE
	$(MAKE) -C $* $(patsubst $*-%,%,$@)
	
%-install: %-compile FORCE
	$(MAKE) -C $* $(patsubst $*-%,%,$@)
