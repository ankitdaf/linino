#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=miniupnpd
PKG_VERSION:=1.6.20110730
PKG_RELEASE:=4

PKG_SOURCE_URL:=http://miniupnp.free.fr/files
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=8bd5c0447b6dc1101b96e958ee67d3ea

include $(INCLUDE_DIR)/package.mk

define Package/miniupnpd
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+iptables +libip4tc
  TITLE:=Lightweight UPnP daemon
  SUBMENU:=Firewall
  URL:=http://miniupnp.free.fr/
  MAINTAINER:=Daniel Dickinson <openwrt@cshore.neomailbox.net>
endef

define Package/miniupnpd/conffiles
/etc/config/upnpd
endef

define Build/Compile
	echo "OpenWRT/$(OPENWRTVERSION)" | tr \(\)\  _ >$(PKG_BUILD_DIR)/os.openwrt
	$(MAKE) -C $(PKG_BUILD_DIR) -f Makefile.linux \
		$(TARGET_CONFIGURE_OPTS) \
		STAGING_DIR="$(STAGING_DIR)" \
		CC="$(TARGET_CC)" \
		TARGET_OPENWRT=1 \
		CFLAGS="$(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(firstword $(wildcard $(KERNEL_BUILD_DIR)/iptables-*/include)) -DIPTABLES_143" \
		LIBS="$(STAGING_DIR)/usr/lib/libip4tc.so"
endef

define Package/miniupnpd/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d $(1)/etc/config $(1)/etc/hotplug.d/iface $(1)/etc/hotplug.d/firewall
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/miniupnpd $(1)/usr/sbin/miniupnpd
	$(INSTALL_BIN) ./files/miniupnpd.init $(1)/etc/init.d/miniupnpd
	$(INSTALL_CONF) ./files/upnpd.config $(1)/etc/config/upnpd
	$(INSTALL_DATA) ./files/miniupnpd.iface.hotplug $(1)/etc/hotplug.d/iface/50-miniupnpd
	$(INSTALL_DATA) ./files/miniupnpd.firewall.hotplug $(1)/etc/hotplug.d/firewall/50-miniupnpd
	$(INSTALL_DIR) $(1)/usr/share/miniupnpd
endef

$(eval $(call BuildPackage,miniupnpd))
