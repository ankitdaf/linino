# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=nvram
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/nvram
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=@LINUX_2_4_BRCM
  TITLE:=Broadcom config utility
  DESCRIPTION:=\
	This package contains an utility to control broadcom's 'nvram' config \\\
	area.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/InstallDev
	mkdir -p $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib{nvram,shared}*.so $(STAGING_DIR)/usr/lib/
endef

define Build/UninstallDev
	rm -f $(STAGING_DIR)/usr/lib/lib{nvram,shared}*.so
endef

define Package/nvram/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib{nvram,shared}*.so $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nvram $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,nvram))
