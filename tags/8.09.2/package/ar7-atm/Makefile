# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=sangam_atm
PKG_VERSION:=D7.03.01.00
PKG_RELEASE:=R2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.bz2
PKG_SOURCE_URL:=http://mirror2.openwrt.org/sources
PKG_MD5SUM:=bc6e9c6adb1be25820c7ee661de8ca7d

include $(INCLUDE_DIR)/package.mk

define KernelPackage/sangam-atm/Default
  SUBMENU:=Network Devices
  DEPENDS:=@TARGET_ar7 +kmod-atm 
  TITLE:=AR7 ADSL driver
  FILES:=$(PKG_BUILD_DIR)/tiatm.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoLoad,50,tiatm)
endef

define KernelPackage/sangam-atm-annex-a
$(call KernelPackage/sangam-atm/Default)
  TITLE+= (Annex A, ADSL over POTS)
endef

define KernelPackage/sangam-atm-annex-a/description
 The AR7 ADSL driver for Annex A (ADSL over POTS).
endef

define KernelPackage/sangam-atm-annex-b
$(call KernelPackage/sangam-atm/Default)
  TITLE+= (Annex B, ADSL over ISDN)
endef

define KernelPackage/sangam-atm-annex-b/description
 The AR7 ADSL driver for Annex B (ADSL over ISDN).
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		modules
endef

define KernelPackage/sangam-atm-annex-a/install
	mkdir -p $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/ar0700mp.bin $(1)/lib/firmware/
	ln -sf ar0700mp.bin $(1)/lib/firmware/ar0700xx.bin
endef

define KernelPackage/sangam-atm-annex-b/install
	mkdir -p $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/ar0700db.bin $(1)/lib/firmware/
	ln -sf ar0700db.bin $(1)/lib/firmware/ar0700xx.bin
endef

$(eval $(call KernelPackage,sangam-atm-annex-a))
$(eval $(call KernelPackage,sangam-atm-annex-b))
