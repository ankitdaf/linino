include $(TOPDIR)/rules.mk

KDIR:=$(BUILD_DIR)/linux-$(KERNEL)-$(BOARD)

lzma-loader-clean:
	$(MAKE) -C lzma-loader clean

lzma-loader-prepare:
	$(MAKE) -C lzma-loader prepare

lzma-loader-compile: lzma-loader-prepare
	$(MAKE) -C lzma-loader compile

ifeq ($(IB),)
$(KDIR)/vmlinux.lzma: $(KDIR)/vmlinux
	cat $^ | $(STAGING_DIR)/bin/lzma e -si -so -eos -lc1 -lp2 -pb2 > $@ || (rm -f $@ && false)

$(KDIR)/loader.tmp.gz: compile
$(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx: $(KDIR)/vmlinux.lzma
endif

ifeq ($(FS),jffs2-8MB)
TRXALIGN:=-a 0x20000
endif
ifeq ($(FS),jffs2-4MB)
TRXALIGN:=-a 0x10000
endif

$(KDIR)/loader.tmp.gz:
	cp $(BUILD_DIR)/loader.gz $@
	echo -ne "\\x00" >> $@

$(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx: $(KDIR)/loader.tmp.gz
	$(STAGING_DIR)/bin/trx -o $@ $(KDIR)/loader.tmp.gz $(KDIR)/vmlinux.lzma $(TRXALIGN) $(KDIR)/root.$(FS)


ifeq ($(KERNEL),2.4)
FSNAME:=$(patsubst jffs2-%,jffs2,$(FS))

ifeq ($(FS),squashfs)
$(BIN_DIR)/openwrt-wap54g-$(FSNAME).trx: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	cp $< $@
	echo -ne '\x01' >> $@
	
install: $(BIN_DIR)/openwrt-wap54g-$(FSNAME).trx
endif


ifneq ($(FS),jffs2-8MB)
$(BIN_DIR)/openwrt-wrt54g3g-$(FSNAME).bin: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	$(STAGING_DIR)/bin/addpattern -4 -p W54F -v v1.99.5 -i $< -o $@ -g

$(BIN_DIR)/openwrt-wrt54g-$(FSNAME).bin: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	$(STAGING_DIR)/bin/addpattern -4 -p W54G -v v4.20.6 -i $< -o $@ -g

$(BIN_DIR)/openwrt-wrt54gs_v4-$(FSNAME).bin: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	$(STAGING_DIR)/bin/addpattern -4 -p W54s -v v1.05.0 -i $< -o $@ -g

install: $(BIN_DIR)/openwrt-wrt54g-$(FSNAME).bin $(BIN_DIR)/openwrt-wrt54gs_v4-$(FSNAME).bin $(BIN_DIR)/openwrt-wrt54g3g-$(FSNAME).bin
endif

ifneq ($(FS),jffs2-4MB)
$(BIN_DIR)/openwrt-wrt54gs-$(FSNAME).bin: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	$(STAGING_DIR)/bin/addpattern -4 -p W54S -v v4.70.6 -i $< -o $@ -g

install: $(BIN_DIR)/openwrt-wrt54gs-$(FSNAME).bin
endif

$(BIN_DIR)/openwrt-motorola-$(FS).bin: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
	$(STAGING_DIR)/bin/motorola-bin $< $@
install: $(BIN_DIR)/openwrt-motorola-$(FS).bin
endif

ifeq ($(IB),)
clean: lzma-loader-clean
prepare: lzma-loader-prepare
compile: lzma-loader-compile
else
clean:
prepare:
compile:
endif
install: $(BIN_DIR)/openwrt-$(BOARD)-$(KERNEL)-$(FS).trx
install-ib:
	mkdir -p $(IB_DIR)/staging_dir_$(ARCH)/bin
	cp -fpR $(STAGING_DIR)/bin/addpattern $(STAGING_DIR)/bin/trx $(STAGING_DIR)/bin/motorola-bin $(IB_DIR)/staging_dir_$(ARCH)/bin
	mkdir -p $(IB_DIR)/build_$(ARCH)/linux-$(KERNEL)-$(BOARD)
	cp -fpR $(BUILD_DIR)/loader.gz $(IB_DIR)/build_$(ARCH)/
	cp -fpR $(KDIR)/vmlinux.lzma $(IB_DIR)/build_$(ARCH)/linux-$(KERNEL)-$(BOARD)/
