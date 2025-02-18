#
# Realtek Semiconductor Corp.
#
# Tony Wu (tonywu@realtek.com)
# Dec. 07, 2008
#

DIR_ROOT ?= ..
DIR_BOARD ?= $(DIR_ROOT)/target

.EXPORT_ALL_VARIABLES:
.PHONY: all romfs clean prune

ifneq (.config,$(wildcard .config))
all: config
else
all: lib app

include .config
include $(DIR_ROOT)/.config
include $(DIR_LINUX)/.config

CONFIG_RTL_WAPI_LOCAL_AS=0
CONFIG_USER_CWMP_OPENSSL=0

ifdef CONFIG_USER_CWMP_OPENSSL_SUPPORT
CONFIG_USER_CWMP_OPENSSL=1
endif
# 8198 and POCKET ROUTER support both wapi psk and wapi cert
# 8196C (not include POCKET ROUTER) only support wapi psk
ifdef CONFIG_RTL_8198_GW
ifdef CONFIG_RTL_WAPI_SUPPORT
ifdef CONFIG_RTL_WAPI_LOCAL_AS_SUPPORT
CONFIG_RTL_WAPI_LOCAL_AS=1
endif
CONFIG_APP_OPENSSL=y
CONFIG_APP_WAPI=y
endif
else # !CONFIG_RTL_8198_GW

ifdef CONFIG_POCKET_ROUTER_SUPPORT
ifdef CONFIG_RTL_WAPI_SUPPORT
ifdef CONFIG_RTL_WAPI_LOCAL_AS_SUPPORT
CONFIG_RTL_WAPI_LOCAL_AS=1
endif
# ############################################
# Because rootfs + 64K wapi-cert is oversize at 2M/16M,
# close WAN apps here just for wapi logo test!!!!!!
CONFIG_APP_PPPD=n
CONFIG_APP_PPTP=n
CONFIG_APP_L2TPD=n
CONFIG_APP_NTPCLIENT=n
CONFIG_APP_DNRD=n
CONFIG_APP_IPROUTE=n
# ############################################
CONFIG_APP_OPENSSL=y
CONFIG_APP_WAPI=y
endif
endif

endif

ifdef CONFIG_RTL_8196C
ifdef CONFIG_RTL_WAPI_SUPPORT
CONFIG_APP_OPENSSL=y
CONFIG_APP_WAPI=y
ifdef CONFIG_RTL_WAPI_LOCAL_AS_SUPPORT
CONFIG_RTL_WAPI_LOCAL_AS=1
endif
endif
endif

ifdef CONFIG_RTL_8196E
ifdef CONFIG_RTL_WAPI_SUPPORT
CONFIG_APP_OPENSSL=y
CONFIG_APP_WAPI=y
ifdef CONFIG_RTL_WAPI_LOCAL_AS_SUPPORT
CONFIG_RTL_WAPI_LOCAL_AS=1
endif
endif
endif

ifdef CONFIG_RTL_819XD
ifdef CONFIG_RTL_WAPI_SUPPORT
CONFIG_APP_OPENSSL=y
CONFIG_APP_WAPI=y
ifdef CONFIG_RTL_WAPI_LOCAL_AS_SUPPORT
CONFIG_RTL_WAPI_LOCAL_AS=1
endif
endif
endif

APMIBINC=
APMIBLIB=
ifeq ($(CONFIG_APP_BOA),y)
APMIBINC = $(DIR_USERS)/boa/apmib/
APMIBLIB = $(DIR_USERS)/boa/apmib/libapmib.so
else
APMIBINC = $(DIR_USERS)/goahead-2.1.1/LINUX/
APMIBLIB = $(DIR_USERS)/goahead-2.1.1/LINUX/apmib.so
endif
	
ifdef CONFIG_RTL_802_1X_CLIENT_SUPPORT
CONFIG_APP_OPENSSL=y
CONFIG_RTL_WAPI_LOCAL_AS=1
endif

ifdef CONFIG_APP_IP6TABLES
CONFIG_APP_IP6TABLES_SUPPORT=1
endif

ifeq ($(CONFIG_RTL_WAPI_SUPPORT),y)
ifeq ($(CONFIG_RSDK_rsdk-1.5.5-5281-EB-2.6.30-0.9.30.3-110714),y) 
CONFIG_APP_OPENSSL-0.9.8I=y
endif
ifeq ($(CONFIG_RSDK_rsdk-1.5.5-4181-EB-2.6.30-0.9.30.3-110225),y)
CONFIG_APP_OPENSSL-0.9.8I=y
endif
ifneq ($(CONFIG_APP_OPENSSL-0.9.8I),y)
CONFIG_APP_OPENSSL-0.9.8B=y
endif
endif

ifdef CONFIG_RTL_COMAPI_WLTOOLS
WLTOOLS=wireless_tools.29
else
WLTOOLS=wireless_tools.25
endif

ifdef CONFIG_RTL_HS2_SUPPORT
CONFIG_APP_HS2=y
endif


CROSS_COMPILE ?= rsdk-linux-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
RANLIB = $(CROSS_COMPILE)ranlib
STRIP = $(CROSS_COMPILE)strip
SSTRIP = $(CROSS_COMPILE)sstrip

CFLAGS += -I$(DIR_TMPFS)/include

CINIT=1

app_y =
ifeq ($(CONFIG_APP_RTK_VOIP),y)
app_y = script/mdev
endif

app_n =
app_  =

lib_y = 
lib_n =
lib_  =

export CFLAGS

# application
app_$(CONFIG_APP_OPENSSL-0.9.8B)	+= openssl-0.9.8b
app_$(CONFIG_APP_OPENSSL-0.9.8I)	+= openssl-0.9.8i
app_$(CONFIG_APP_BUSYBOX)		+= busybox
app_$(CONFIG_APP_GOAHEAD)		+= goahead-2.1.1
app_$(CONFIG_APP_BOA)			+= boa
app_$(CONFIG_APP_ADAPTER_API)       	+= adapter-api
ifeq ($(CINIT), 1)
app_$(CONFIG_APP_SCRIPT)		+= script/cinit
else
app_$(CONFIG_APP_SCRIPT)		+= script
endif
app_$(CONFIG_APP_SQUASHFS40)		+= squashfs4.0/squashfs-tools
app_$(CONFIG_APP_IPROUTE)		+= iproute2-2.6.29-1
app_$(CONFIG_APP_IPTABLES)		+= iptables-1.4.4
app_$(CONFIG_APP_L7FILTER_PAT)		+= l7-protocols
app_$(CONFIG_APP_NTPCLIENT)		+= ntpclient
app_$(CONFIG_APP_DHCPV6)		+= wide-dhcpv6
app_$(CONFIG_APP_RADVD)			+= radvd-0.9.1
app_$(CONFIG_APP_ECMH)			+= ecmh
app_$(CONFIG_APP_GDBSERVER)             += gdb
app_$(CONFIG_APP_USBMOUNT)		+= usbmount
app_$(CONFIG_APP_VSFTPD)		+= vsftpd-2.3.2
app_$(CONFIG_APP_DOSFSCK)		+= dosfstools-2.11/dosfsck
app_$(CONFIG_APP_MKDOSFS)		+= dosfstools-2.11/mkdosfs
app_$(CONFIG_APP_NTFS3G)		+= ntfs-3g-2010.10.2
app_$(CONFIG_APP_MP)			+= mp-daemon
app_$(CONFIG_APP_CLOUD)			+= cloud
app_$(CONFIG_LIB_LIBDAEMON)		+= libdaemon-0.14
#CONFIG_APP_SAMBA-3.0.37 OR CONFIG_APP_SAMBA-3.0.24 at most one will be chose
#app_$(CONFIG_APP_SAMBA-3.0.37)		+= samba-3.0.37/source
app_$(CONFIG_APP_SAMBA)		+= samba
#app_$(CONFIG_APP_SMABA-3.2.15)		+= samba
#ifeq($(CONFIG_APP_SAMBA-3.0.24),y)
#else
#ifeq($(CONFIG_APP_SAMBA-3.0.37),y)
#else
#ifeq($(CONFIG_APP_SAMBA-3.2.15),y)
#endif

app_$(CONFIG_APP_GPROXY)		+= gproxy
app_$(CONFIG_APP_IGMPPROXY)		+= igmpproxy
app_$(CONFIG_APP_MLDPROXY)      += mldproxy
app_$(CONFIG_APP_PATHSEL)		+= 11s-PathSelection
app_$(CONFIG_APP_WIRELESSTOOLS)		+= $(WLTOOLS)
app_$(CONFIG_APP_DNRD)			+= dnrd-2.12.1/src
app_$(CONFIG_APP_ROUTED)		+= routed
app_$(CONFIG_APP_RTK_CMD)		+= rtk_cmd 
app_$(CONFIG_APP_PPPD)			+= ppp-2.4.4/pppd
app_$(CONFIG_APP_PPTP)			+= pptp-1.7.2
app_$(CONFIG_APP_L2TPD)			+= l2tpd
app_$(CONFIG_APP_DNSMASQ)		+= dnsmasq-2.33
app_$(CONFIG_APP_MINI_UPNP)		+= mini_upnp
app_$(CONFIG_APP_WSC)			+= wsc 
app_$(CONFIG_APP_AUTH)			+= auth/src 
app_$(CONFIG_APP_IWCONTROL)		+= auth/src/dlisten
app_$(CONFIG_APP_AVAHI)			+= avahi-0.6.31
app_$(CONFIG_APP_HOSTAPD)		+= hostapd-2.0/hostapd
app_$(CONFIG_APP_UDHCPD)		+= udhcp-0.9.9-pre
app_$(CONFIG_APP_BRCTL)			+= bridge-utils
app_$(CONFIG_APP_MINIIGD)		+= miniigd
app_$(CONFIG_APP_RELOAD)		+= rc
app_$(CONFIG_APP_LLTDD)			+= lltdd/native-linux
app_$(CONFIG_APP_ORAYDDNS)			+= orayddns
app_$(CONFIG_APP_UPDATEDD)			+=  updatedd-2.5
app_$(CONFIG_APP_DISCOVER)			+=  discover
app_$(CONFIG_APP_IAPP)			+= IAPP 
ifeq ($(CONFIG_APP_RTK_VOIP),y)
ifeq ($(CONFIG_APP_RTK_VOIP_E8C),y)
lib_$(CONFIG_APP_RTK_VOIP)		+= rtk_voip-e8c		# pkshih: build this before tr069
app_$(CONFIG_APP_RTK_VOIP)		+= rtk_voip-e8c		# pkshih: build this before tr069
else
lib_$(CONFIG_APP_RTK_VOIP)		+= rtk_voip		# pkshih: build this before tr069
app_$(CONFIG_APP_RTK_VOIP)		+= rtk_voip		# pkshih: build this before tr069
endif
endif
app_$(CONFIG_APP_PMC_UTILS)		+= pmc_utils
app_$(CONFIG_APP_NFBI)			+= nfbi
app_$(CONFIG_APP_HOSTAPD_SLAVE)			+= hostapd_slave
app_$(CONFIG_APP_RTK_INBAND_CTL)	+= hcm
app_$(CONFIG_APP_RTK_INBAND_HOST)       += rtk_inbandHost
app_$(CONFIG_APP_CTORRENT)              += ctorrent-dnh3.3.2
app_$(CONFIG_APP_DCTS)			+= dctcs.src/src
app_$(CONFIG_APP_SNMP)			+= net-snmp-5.4.1
app_$(CONFIG_APP_HS2)			+= hs2
app_$(CONFIG_APP_IOH)			+= ioh
app_$(CONFIG_APP_NFBI_HOST)		+= nfbihost/nfbi
app_$(CONFIG_APP_TR069)			+= cwmp-tr069_v2
app_$(CONFIG_APP_UWIFI)		+= uWiFi
app_$(CONFIG_APP_NMBS)		+= nbserver
app_$(CONFIG_APP_ALSA_AUDIO)	+= alsa_related
app_$(CONFIG_APP_AUTORUNIMG)    += autorun_img_tool
app_$(CONFIG_APP_SIMPLE_CONFIG)    += simple_config
app_$(CONFIG_APP_APPLE_MFI_WAC)	+= mfi_wac

# USB3G
app_$(CONFIG_APP_COMGT)			+= comgt.0.32
app_$(CONFIG_APP_CHAT)			+= ppp-2.4.4/chat
app_$(CONFIG_APP_LIBUSB)		+= libusb-0.1.12
app_$(CONFIG_APP_USBMODESWITCH)		+= usb-modeswitch
app_$(CONFIG_APP_MBPK_EJECT)		+= mbpk_eject
app_$(CONFIG_APP_USBMODESWITCH_DATA)	+= usb-modeswitch-data
app_$(CONFIG_APP_USBUTILS)		+= usbutils-0.86
app_$(CONFIG_APP_HUBCTRL)		+= hub-ctrl
app_$(CONFIG_APP_MNET)		        += mnet

# debug & test
app_$(CONFIG_APP_CLE_SHELL)		+= cle-shell
app_$(CONFIG_APP_UTILS)			+= utils
app_$(CONFIG_APP_IPERF)			+= iperf-2.0.4
app_$(CONFIG_APP_DHRYSTONE)		+= dhrystone
app_$(CONFIG_APP_IOZONE)		+= iozone3_327/src/current
app_$(CONFIG_APP_EXAMPLE)		+= example
app_$(CONFIG_APP_LTP)			+= ltp
##################### WHZ STA #########################
app_$(CONFIG_APP_TEST)			+= whztest
app_$(CONFIG_APP_EV_TOOLS)		+= ev_tools
app_$(CONFIG_APP_EV_RCSERVER)		+= ev_rcserver
##################### WHZ END #########################

# wapi related
#app_$(CONFIG_APP_OPENSSL)		+= openssl-0.9.8b 
app_$(CONFIG_APP_OPENSSL)		+= 	

#app_$(CONFIG_APP_OPENSSL-0.9.8B)	+= openssl-0.9.8b
#app_$(CONFIG_APP_OPENSSL-0.9.8I)	+= openssl-0.9.8i

app_$(CONFIG_APP_WAPI)			+= wapi_utils/udp_sock wapi_utils/rwWapiFiles \
					  wapi_utils/other_tools wapi_utils/wapi_scripts
app_$(CONFIG_APP_HOSTAPD_HCM)           += hostapd-0.6.10/hostapd inband_lib
app_$(CONFIG_APP_DLNA_DMS)		+= dlna_dms

app_$(CONFIG_APP_MT_DAAPD)		+= mt-daapd-0.2.4.2

app_$(CONFIG_APP_SPEEDTEST)		+= speedtest
app_$(CONFIG_APP_FLATFSD) +=flatfsd
app_$(CONFIG_APP_SIGMA_UTILS)		+=  sigma_utils
# libraries
#lib_$(CONFIG_LIBNL) += iw-0.9.17
#ifdef CONFIG_APP_HOSTAPD
lib_$(CONFIG_APP_OPENSSL-0.9.8B)	+= openssl-0.9.8b
#endif
lib_$(CONFIG_APP_HOSTAPD_HCM)		+= inband_lib
lib_$(CONFIG_APP_HOSTAPD_SLAVE)		+= inband_lib
lib_$(CONFIG_APP_RTK_INBAND_CTL)	+= rtk_inbandLib
lib_$(CONFIG_APP_RTK_INBAND_HOST)	+= rtk_inbandLib
lib_$(CONFIG_LIB_NL) += libnl-1.1
lib_$(CONFIG_APP_FLEX)			+= flex-2.5.33
lib_$(CONFIG_LIB_Z)			+= zlib-1.2.5
lib_$(CONFIG_APP_PPPD)			+= ppp-2.4.4/pppd/plugins/rp-pppoe

ifeq ($(CONFIG_APP_SNMP),y)
lib_$(CONFIG_APP_GOAHEAD)		+= goahead-2.1.1
endif
ifeq ($(CONFIG_APP_TR069),y)
lib_$(CONFIG_APP_GOAHEAD)		+= goahead-2.1.1
endif
ifdef CONFIG_RTL_802_1X_CLIENT_SUPPORT
#lib_$(CONFIG_APP_OPENSSL)		+= openssl-0.9.8b
lib_$(CONFIG_APP_OPENSSL-0.9.8B)	+= openssl-0.9.8b
lib_$(CONFIG_APP_OPENSSL-0.9.8I)	+= openssl-0.9.8i
endif
app_$(CONFIG_LIB_FUSE)			+= fuse-2.9.0
app_$(CONFIG_APP_MINIDLNA)  +=minidlna
app_$(CONFIG_APP_CAPWAP)  += capwap-0.93.3
#app_$(CONFIG_RTL_USERSPACE_WTDOG)       += watchdog
app_$(CONFIG_APP_BLUEZ)  +=bluez-4.96
app_$(CONFIG_APP_RTK_BLUETOOTH_FM)  +=rtk_bluetooth_firmware
app_$(CONFIG_APP_UPIMAGE) += upImage/lrzsz/lrzsz-0.12.20/
app_$(CONFIG_APP_UPIMAGE) += upImage/flash_writer

app_$(CONFIG_APP_CPU_UTILIZATION)       += cpu
app_$(CONFIG_APP_EXFAT_FUSE)		+= fuse-exfat-1.1.0
app_$(CONFIG_APP_TRACEROUTE)		+= traceroute-2.0.21
app_$(CONFIG_APP_UBUS)		+= ubus-2014-09-17
lib:
ifneq ($(lib_y),)
	$(MAKE) $(lib_y) || exit $$?
else
	@echo "No libs specified"
endif
app:
	$(MAKE) $(app_y) || exit $$?
endif
#
# add directory dependancies here
#
.PHONY: ulibs romfs $(lib_y) $(app_y)

# We create the target directory of the symlink if it does
# not exist so the test in check-symlink works and we have a
# directory for generated filesas used by some architectures.
define create-symlink
	if [ ! -L cle-shell ]; then                                      \
			echo '  SYMLINK cle-shell -> ../../../ICTest/users/cle-shell/'; \
			ln -fsn ../../../ICTest/users/cle-shell/ cle-shell;                         \
	fi
endef

prepare:
ifeq ($(CONFIG_APP_AVAHI), y)
	@cd ./avahi-0.6.31; \
	if [ ! -e Makefile ]; then \
		AR=$(CROSS_COMPILE)ar \
		AS="$(CROSS_COMPILE)gcc -c -Os -pipe -fno-caller-saves -fpic -DGETTEXT_PACKAGE" \
		LD=$(CROSS_COMPILE)ld \
		NM=$(CROSS_COMPILE)nm \
		CC="$(CROSS_COMPILE)gcc" \
		GCC="$(CROSS_COMPILE)gcc" \
		RANLIB=$(CROSS_COMPILE)ranlib \
		STRIP=$(CROSS_COMPILE)strip \
		OBJCOPY=$(CROSS_COMPILE)objcopy \
		OBJDUMP=$(CROSS_COMPILE)objdump \
		SIZE=$(CROSS_COMPILE)size \
		CFLAGS="-Os -pipe -fno-caller-saves -fpic -DGETTEXT_PACKAGE -DNDEBUG -DDISABLE_SYSTEMD -I$(DIR_ROOT)/users/libdaemon-0.14/" \
		LIBDAEMON_CFLAGS="-I$(DIR_ROOT)/users/libdaemon-0.14/libdaemon/" \
		LIBDAEMON_LIBS="-L$(DIR_ROOT)/users/libdaemon-0.14/libdaemon/.libs/ -ldaemon" \
		ac_cv_header_sys_capability_h=no \
		./configure --target=mips-linux --host=mips-linux --build=i686-linux-gnu \
		--program-prefix="" --program-suffix="" --prefix=/usr --exec-prefix=/usr \
		--bindir=/usr/bin --sbindir=/usr/sbin --libexecdir=/usr/lib --sysconfdir=/etc \
		--datadir=/usr/share --localstatedir=/var --mandir=/usr/man --infodir=/usr/info \
		--disable-nls --enable-shared --enable-static --disable-glib --disable-gobject \
		--disable-qt3 --disable-qt4 --disable-gtk --disable-gtk3 --with-xml=none --disable-dbm --disable-gdbm \
		--enable-libdaemon --disable-python --disable-pygtk --disable-python-dbus --disable-mono --disable-monodoc \
		--disable-doxygen-doc --disable-doxygen-dot --disable-doxygen-man --disable-doxygen-rtf --disable-doxygen-xml \
		--disable-doxygen-chm --disable-doxygen-chi --disable-doxygen-html --disable-doxygen-ps --disable-doxygen-pdf \
		--disable-xmltoman --with-distro=none --with-avahi-user=nobody --with-avahi-group=nogroup \
		--with-autoipd-user=nobody --with-autoipd-group=nogroup --disable-stack-protector --disable-dbus; \
	fi; \
	make; \
	cd ..
endif

ifeq ($(CONFIG_LIB_LIBDAEMON), y)
	@cd ./libdaemon-0.14; \
	if [ ! -e Makefile ]; then \
		AR=$(CROSS_COMPILE)ar \
		AS="$(CROSS_COMPILE)gcc -c -Os -pipe -fno-caller-saves -fpic" \
		LD=$(CROSS_COMPILE)ld \
		NM=$(CROSS_COMPILE)nm \
		CC="$(CROSS_COMPILE)gcc" \
		GCC="$(CROSS_COMPILE)gcc" \
		RANLIB=$(CROSS_COMPILE)ranlib \
		STRIP=$(CROSS_COMPILE)strip \
		OBJCOPY=$(CROSS_COMPILE)objcopy \
		OBJDUMP=$(CROSS_COMPILE)objdump \
		SIZE=$(CROSS_COMPILE)size \
		CFLAGS="-Os -pipe -fno-caller-saves -fpic " \
		./configure --target=mips-linux --host=mips-linux --build=i686-linux-gnu \
		--program-prefix="" --program-suffix="" --prefix=/usr --exec-prefix=/usr \
		--bindir=/usr/bin --sbindir=/usr/sbin --libexecdir=/usr/lib --sysconfdir=/etc \
		--datadir=/usr/share --localstatedir=/var --mandir=/usr/man --infodir=/usr/info \
		--disable-nls --enable-shared --disable-static --disable-lynx \
		ac_cv_func_setpgrp_void=yes; \
	fi; \
	make; \
	cd ..
endif
ifeq ($(CONFIG_APP_RTK_API_TEST_CASE),y)
	@if [ ! -e ./CUnit-2.1-2/Makefile ]; then \
                cd ./CUnit-2.1-2; \
                pwd; \
                ./configure --host=mips-linux; \
                make;\
                cd ..; \
        fi
endif
ifeq ($(CONFIG_APP_CLE_SHELL),y)
	@$(create-symlink)
endif
ifeq ($(CONFIG_APP_UTILS),y)
	@if [ ! -L utils ]; then \
			echo '  SYMLINK utils -> ../../../ICTest/users/utils/'; \
			ln -fsn ../../../ICTest/users/utils/ utils; \
	fi
endif
ifeq ($(CONFIG_APP_IPERF),y)
	@if [ ! -e ./iperf-2.0.4/Makefile ]; then \
		cd ./iperf-2.0.4; \
		ac_cv_func_malloc_0_nonnull=yes ./configure --host=mips-linux --disable-threads --disable-web100; \
	fi
endif
ifeq ($(CONFIG_APP_BLUEZ),y)
	@echo "Generate lib";
	mkdir -p lib;
	@echo "build expat";
	@if [ ! -e ./expat-2.1.0/Makefile ]; then \
		cd ./expat-2.1.0; \
		CFLAGS="-fPIC" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib"; \
		make; \
		make install; \
		cd -; \
	fi
	
	@echo "build dbus";
	@if [ ! -d ./dbus-1.8.0 ]; then \
		tar -xvzf dbus-1.8.0.tar.gz;\
	fi
	@if [ ! -e ./dbus-1.8.0/Makefile ]; then \
		cd ./dbus-1.8.0; \
		CFLAGS="-fPIC" PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" ./configure --enable-abstract-sockets --disable-systemd --host=mips-linux --prefix="$(DIR_ROOT)/users/lib" \
		CPPFLAGS="-I$(DIR_ROOT)/users/lib/include" LDFLAGS="-L$(DIR_ROOT)/users/lib/lib"; \
		make; \
		make install; \
		cd -; \
	fi

	@echo "build libusb";
	@if [ ! -e ./libusb-1.0.9/Makefile ]; then \
		cd ./libusb-1.0.9; \
		CFLAGS="-fPIC" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib"; \
		make; \
		make install; \
		cd -; \
	fi

	@echo "build libffi-3.0.13";
	@if [ ! -e ./libffi-3.0.13/Makefile ]; then \
		cd ./libffi-3.0.13; \
		CFLAGS="-fPIC" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib"; \
		make; \
		make install; \
		cd -; \
	fi

	@echo "build gettext-0.18.3.1";
	@if [ ! -d ./gettext-0.18.3.1 ]; then \
		tar -xvzf gettext-0.18.3.1.tar.gz;\
	fi

	@if [ ! -e ./gettext-0.18.3.1/Makefile ]; then \
		cd ./gettext-0.18.3.1; \
		CFLAGS="-fPIC" PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib" \
		CPPFLAGS="-I$(DIR_ROOT)/users/lib/include" LDFLAGS="-L$(DIR_ROOT)/users/lib/lib"; \
		make; \
		make install; \
		cd -; \
	fi

	@echo "build libiconv"
	@if [ ! -e ./libiconv-1.14/Makefile ]; then \
		cd ./libiconv-1.14; \
		CFLAGS="-fPIC" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib" --disable-nls --enable-static=yes --enable-shared=no --enable-fast-install=no; \
		make; \
		make install; \
		cd -; \
	fi
	@echo "build zlib"
	@if ! grep "libz.a" -q ./zlib-1.2.8/Makefile; then \
		cd ./zlib-1.2.8; \
		CFLAGS="-fPIC" CC=$(CROSS_COMPILE)gcc ./configure --prefix="$(DIR_ROOT)/users/lib"; \
		make; \
		make install; \
		cd -; \
	fi

	@echo "build glib";
	@if [ ! -e ./glib-2.36.0/Makefile ]; then \
		cd ./glib-2.36.0; \
		echo ac_cv_type_long_long=yes>mips-linux.cache; \
		echo glib_cv_stack_grows=no>>mips-linux.cache; \
		echo glib_cv_uscore=no>>mips-linux.cache; \
		echo c_cv_func_posix_getpwuid_r=yes>>mips-linux.cache; \
		echo ac_cv_func_posix_getpwuid_r=yes>>mips-linux.cache; \
		echo ac_cv_func_posix_getgrgid_r=yes>>mips-linux.cache; \
		PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" CFLAGS="-fPIC" ./configure --host=mips-linux --prefix="$(DIR_ROOT)/users/lib" \
		CPPFLAGS="-I$(DIR_ROOT)/users/lib/include" LDFLAGS="-L$(DIR_ROOT)/users/lib/lib" \
		--cache-file=mips-linux.cache; \
		make; \
		make install; \
		cd -; \
	fi
	@echo "build alsa-1.0.25"
	@if [ ! -e ./alsa-lib-1.0.25/Makefile ]; then \
		cd ./alsa-lib-1.0.25; \
		CFLAGS="-fPIC" ./configure --prefix="$(DIR_ROOT)/users/lib" --build=i686-pc-linux-gnu --host=mips-linux --disable-python; \
	        touch ./configure; \
                touch ./config.status; \
                touch ./Makefile.in; \
                touch ./Makefile; \
                touch ./include/config.h.in; \
		make; \
		make install; \
		cd -; \
	fi


	@echo "build libsndfile"
	@if [ ! -e ./libsndfile-1.0.25/Makefile ]; then \
		cd ./libsndfile-1.0.25; \
		cd -; \
	fi

	@echo "build bluez";
	@if [ ! -e ./bluez-4.96/Makefile ]; then \
		cd ./bluez-4.96; \
		CFLAGS="-fPIC" ac_cv_lib_glib_2_0_g_slist_free_full=yes PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" ./configure --disable-systemd --enable-static=yes --host=mips-linux \
		--disable-audio \
		CPPFLAGS="-I$(DIR_ROOT)/users/lib/include -I$(DIR_ROOT)/users/lib/include/glib-2.0 -I$(DIR_ROOT)/users/lib/include/libusb-1.0 -I$(DIR_ROOT)/users/lib/include/sys -I$(DIR_ROOT)/users/lib/include/alsa -I$(DIR_ROOT)/users/lib/include/dbus-1.0" LDFLAGS="-L$(DIR_ROOT)/users/lib/lib"; \
		cd -; \
	fi
endif

ifeq ($(CONFIG_APP_UBUS),y)
	@echo "Generate lib";
	mkdir -p lib;
	#json-c
	@echo "build json-c"
	@if [ ! -e ./json-c-0.12/Makefile ]; then \
		tar -xvzf json-c-0.12.tar.gz; \
		cd ./json-c-0.12; \
		CFLAGS="-fPIC -DPIC" ac_cv_func_malloc_0_nonnull=yes ac_cv_func_realloc_0_nonnull=yes ac_cv_have_decl_isnan=yes ac_cv_have_decl_isinf=yes ./configure --prefix="$(DIR_ROOT)/users/lib" --host=mips-linux; \
		make V=s; \
		make install; \
		cd -; \
	fi
	@echo "build libubox"
	@if [ ! -e ./libubox-2014-08-04/Makefile ]; then \
		tar -xvzf  libubox-2014-08-04-dffbc09baf71b294185a36048166d00066d433b5.tar.gz; \
		cd ./libubox-2014-08-04; \
		sed 's/OPTION(BUILD_LUA \"build Lua plugin\" ON)/OPTION(BUILD_LUA \"build Lua plugin\" OFF)/g' -i CMakeLists.txt; \
		sed 's/PKG_CHECK_MODULES(JSONC json-c json)/PKG_CHECK_MODULES(JSONC json-c)/g' -i CMakeLists.txt; \
		LDFLAGS="-lm" PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" cmake -DCMAKE_INSTALL_PREFIX="$(DIR_ROOT)/users/lib/" -DCMAKE_FIND_ROOT_PATH="$(DIR_ROOT)/users/lib/" .; \
		make; \
		make install; \
		cd -; \
	fi
	@echo "build ubus"
	@if [ ! -e ./ubus-2014-09-17/Makefile ]; then \
		tar -xvzf ubus-2014-09-17-4c4f35cf2230d70b9ddd87638ca911e8a563f2f3.tar.gz; \
		cd ./ubus-2014-09-17; \
		sed 's/OPTION(BUILD_LUA \"build Lua plugin\" ON)/OPTION(BUILD_LUA \"build Lua plugin\" OFF)/g' -i CMakeLists.txt; \
		sed 's/OPTION(ENABLE_SYSTEMD \"systemd support\" ON)/OPTION(ENABLE_SYSTEMD \"systemd support\" OFF)/g' -i CMakeLists.txt; \
		sed '16a'"INCLUDE_DIRECTORIES($(DIR_ROOT)/users/lib/include)" -i CMakeLists.txt; \
		sed '16a'"INCLUDE_DIRECTORIES($(DIR_ROOT)/users/lib/include/json-c)" -i CMakeLists.txt; \
		sed '16a'"LINK_DIRECTORIES($(DIR_ROOT)/users/lib/lib)" -i CMakeLists.txt; \
		sed '16a'"ADD_DEFINITIONS(-DJSONC)" -i CMakeLists.txt; \
		PKG_CONFIG_PATH="$(DIR_ROOT)/users/lib/lib/pkgconfig" cmake -DCMAKE_INSTALL_PREFIX="$(DIR_ROOT)/users/lib/" -DCMAKE_FIND_ROOT_PATH="$(DIR_ROOT)/users/lib" .; \
		sed '526a'"romfs:" -i Makefile; \
		sed '527a\\t$(ROMFSINST) ubusd /bin' -i Makefile; \
		sed '528a\\t$(ROMFSINST) ubus /bin' -i Makefile; \
		sed '529a\\t$(ROMFSINST) examples/client /bin' -i Makefile; \
		sed '530a\\t$(ROMFSINST) examples/server /bin' -i Makefile; \
		sed '531a\\t$(ROMFSINST) \"*.so\" /lib' -i Makefile; \
		sed '532a\\t$(ROMFSINST) ../libubox-2014-08-04/\"*.so\" /lib' -i Makefile; \
		cd -; \
	fi
endif
#ifeq ($(CONFIG_APP_OPENSSL),y)
ifeq ($(CONFIG_APP_OPENSSL-0.9.8B),y)
	@cd ./openssl-0.9.8b; \
	if [ $(CONFIG_RTL_WAPI_LOCAL_AS) = 1 -o $(CONFIG_USER_CWMP_OPENSSL) = y ]; then \
		if [ ! -f dlib_config_done ]; then \
			./Configure shared $(CROSS_TARGET); make depend; \
			rm -f slib_config_done; touch dlib_config_done; \
			make clean; \
			cp Makefile.DLibForWapi Makefile; \
			cp test/Makefile.wapi test/Makefile; \
		fi;\
	else\
		if [ ! -f slib_config_done ]; then \
			./Configure no-threads no-hw no-shared $(CROSS_TARGET); make depend; \
			rm -f dlib_config_done; touch slib_config_done;\
			make clean; \
			cp Makefile.SLibForWapi Makefile; \
			cp test/Makefile.wapi test/Makefile; \
		fi;\
	fi;\
	cd -;
endif
ifeq ($(CONFIG_APP_OPENSSL-0.9.8I),y)
	@cd ./openssl-0.9.8i; \
	if [ $(CONFIG_RTL_WAPI_LOCAL_AS) = 1 -o $(CONFIG_USER_CWMP_OPENSSL) = y ]; then \
		if [ ! -f dlib_config_done ]; then \
			./Configure shared rsdk-linux; make depend; \
			rm -f slib_config_done; touch dlib_config_done; \
			make clean; \
			cp Makefile.DLibForWapi Makefile; \
			cp test/Makefile.wapi test/Makefile; \
		fi;\
	else\
		if [ ! -f slib_config_done ]; then \
			./Configure no-threads no-hw no-shared rsdk-linux; make depend; \
			rm -f dlib_config_done; touch slib_config_done;\
			make clean; \
			cp Makefile.SLibForWapi Makefile; \
			cp test/Makefile.wapi test/Makefile; \
		fi;\
	fi;\
	cd -;
endif

ifeq ($(CONFIG_APP_RTK_VOIP),y)
ifeq ($(CONFIG_APP_RTK_VOIP_E8C),y)
	ln -fs $(DIR_LINUX)/.config rtk_voip-e8c/.linux_config
	make -C rtk_voip-e8c prepare
else
	ln -fs $(DIR_LINUX)/.config rtk_voip/.linux_config
	make -C rtk_voip prepare
endif
endif

ifeq ($(CONFIG_APP_IPTABLES),y)
	@cd ./iptables-1.4.4; \
	if [ $(CONFIG_APP_IP6TABLES_SUPPORT) = 1 ]; then \
		if [ ! -f ip6tables_config_done ]; then \
			./configure --host=mips-linux --with-ksource=../../linux-2.6.30 --enable-static --disable-shared CFLAGS=-Os; \
			make depend; \
			rm -f iptables_config_done; touch ip6tables_config_done; \
			make clean; \
			cp Makefile.ip6 Makefile; \
			cp ./extensions/GNUmakefile.ip6 ./extensions/GNUmakefile; \
		fi; \
	else\
		if [ ! -f iptables_config_done ]; then \
			./configure --host=mips-linux --with-ksource=../../linux-2.6.30 --enable-static --disable-shared --disable-ipv6 CFLAGS=-Os; \
			make depend; \
			rm -f ip6tables_config_done; touch iptables_config_done; \
			make clean; \
			cp Makefile.RSDK Makefile; \
			cp ./extensions/GNUmakefile.RSDK ./extensions/GNUmakefile; \
		fi; \
	fi; \
	cd -
endif

ifeq ($(CONFIG_APP_GDBSERVER),y)
	echo 'make gdbserver';
	cd ./gdb; \
	if [ ! -f gdb_config_done ]; then \
		cd gdb-6.8; ./configure --target=mips-linux --host=i686-pc-linux-gnu --prefix=$(shell pwd)/gdb/gdb-host;  \
		cp Makefile.RSDK Makefile; \
		cd gdb/gdbserver; \
		./configure --target=mips-linux --host=mips-linux --prefix=$(shell pwd)/gdb/gdbserver-6.8; \
		cd ../../../; \
		rm -f gdb_config_done; touch gdb_config_done; \
	fi; \
	cd ..
endif
ifeq ($(CONFIG_LIB_Z),y)
	@if ! grep "libz.a" -q ./zlib-1.2.5/Makefile; then \
		cd ./zlib-1.2.5/; \
		CC=rsdk-linux-gcc ./configure --prefix=$(DIR_USERS)/zlib-1.2.5/install; \
	fi
endif

ifeq ($(CONFIG_APP_MT_DAAPD),y)
	@echo 'make zlib-1.2.3';
	cd ./zlib-1.2.3; \
	if [ ! -f zlib-1.2.3_config_done ]; then \
		./configure; \
		cp Makefile.zlib Makefile; \
		rm -f zlib-1.2.3_config_done; touch zlib-1.2.3_config_done; \
	fi; \
	make; \
	cd ..

	@echo 'make gdbm-1.8.3'; 
	cd ./gdbm-1.8.3; \
	if [ ! -f gdbm-1.8.3_config_done ]; then \
		./configure --host=mips-linux --build=i686-pc-linux-gnu; \
		cp Makefile.gdbm Makefile; \
		cp libtool.gdbm libtool; \
		rm -f gdbm-1.8.3_config_done; touch gdbm-1.8.3_config_done; \
	fi; \
	make; \
	cd ..

	@echo 'make libid3tag';
	cd ./libid3tag-0.15.1b; \
	if [ ! -f libid3tag_config_done ]; then \
		./configure --build=mips-linux --host=i686-pc-linux-gnu \
		--enable-shared \
		--disable-static \
		CPPFLAGS="-I../zlib-1.2.3/" \
		LDFLAGS="-L../zlib-1.2.3/"; \
		cp Makefile.id3tag Makefile; \
		cp libtool.id3tag libtool; \
		cd ./msvc++; \
		cp Makefile.id3tag Makefile; \
		cd ..;\
		rm -f libid3tag_config_done; touch libid3tag_config_done; \
	fi; \
	make; \
	cd ..

	@echo 'make mt-daapd'; \
	cd ./mt-daapd-0.2.4.2; \
	if [ ! -f mt-daapd_config_done ]; then \
		./configure --host=mips-linux \
		--with-gdbm-includes=../gdbm-1.8.3/ \
		--with-gdbm-libs=../gdbm-1.8.3/ \
		--with-id3tag=../libid3tag-0.15.1b/ \
		--with-id3tag-libs=../libid3tag-0.15.1b/.libs/ \
		LIBS="-lgdbm -L$(DIR_ROOT)/users/gdbm-1.8.3/ -lid3tag -L$(DIR_ROOT)/users/libid3tag-0.15.1b/.libs/ -lz -L$(DIR_ROOT)/users/zlib-1.2.3/" \
		ac_cv_func_setpgrp_void=yes; \
		cp Makefile.daapd Makefile; \
		cd ./src; cp Makefile.daapd Makefile; cd ..; \
		cd ./admin-root; cp Makefile.daapd Makefile; cd ..; \
		cd ./contrib; cp Makefile.daapd Makefile; cd ..; \
		cd ./debian; cp Makefile.daapd Makefile; cd ..; \
		rm -f mt-daapd_config_done; touch mt-daapd_config_done; \
	fi; \
	make; \
	cd ..
endif

ifeq ($(CONFIG_APP_RADVD),y)
	@if [ ! -e ./radvd-0.9.1/Makefile ]; then \
		cd ./radvd-0.9.1; \
		./configure --host=mips-linux; \
		touch Makefile.in; \
	fi
endif

ifeq ($(CONFIG_APP_UPIMAGE),y)
	@cd ./upImage/lrzsz/lrzsz-0.12.20; \
	if [ ! -f liblrzsz_config_done ]; then \
		./configure --prefix=/bin/ --host=mips-linux --enable-pubdir=/var;\
		rm -f liblrzsz_config_done; touch liblrzsz_config_done; \
		echo "romfs:" >> Makefile; \
		echo "	$(ROMFSINST)  src/lrz /bin/lrz" >> Makefile;\
		echo "	$(ROMFSINST)  src/lsz /bin/lsz" >> Makefile;\
	fi; \
	cd -;
endif

ifeq ($(CONFIG_APP_EXFAT_FUSE),y)
ifneq ($(CONFIG_LIB_FUSE), y)
	$(error fuse library should selected by exfat fuse)
endif
endif

ifeq ($(CONFIG_LIB_FUSE), y)
	if [ ! -e ./fuse-2.9.0/Makefile ]; then \
		cd ./fuse-2.9.0; \
		./configure --host=mips-linux; \
		echo "romfs:" >> Makefile; \
		cd -; \
	fi
endif

prepare_lib:
ifeq ($(CONFIG_APP_LIBICONV),y)
	cd ./libiconv-1.14; \
	if [ ! -f libiconv_config_done ]; then \
		./configure --host=mips-linux --disable-nls --enable-static=yes --enable-shared=no --enable-fast-install=no; \
		cp Makefile.libiconv Makefile; \
		cp ./preload/Makefile.libiconv ./preload/Makefile; \
		rm -f libiconv_config_done; touch libiconv_config_done; \
	fi; \
	make; \
	cd ..
endif

prepare_app:
ifeq ($(CONFIG_APP_SNMP),y)
	cd ./net-snmp-5.4.1; \
	./configure.rtk-snmp CROSS_COMPILE=$(CROSS_COMPILE) APMIBINC=$(APMIBINC) APMIBLIB=$(APMIBLIB); \
	cd -
endif

$(lib_y): prepare prepare_lib
	[ ! -d "$@" ] || $(MAKE) -C $@ || exit $$?

$(app_y): prepare prepare_app
	[ ! -d "$@" ] || $(MAKE) -C $@ || exit $$?

#%_only:
#	$(MAKE) -C $(@:_only=)
#
#%_clean:
#	$(MAKE) -C $(@:_clean=) clean; true
#
#%_romfs:
#	$(MAKE) -C $(@:_romfs=) romfs

ulibs:
	[ -e $(DIR_ROMFS)/lib ] || mkdir -p $(DIR_ROMFS)/lib
	for i in $(lib_y) ; do \
		[ ! -d $$i ] || $(MAKE) -C $$i romfs || exit $$? ; \
	done

romfs:
	[ -e $(DIR_ROMFS)/bin ] || mkdir -p $(DIR_ROMFS)/bin
	for i in $(app_y) ; do \
		[ ! -d $$i ] || $(MAKE) -C $$i romfs || exit $$? ; \
	done

clean:
	-for i in $(app_y) $(app_n) $(app_) $(lib_y) $(lib_n) $(lib_) ; do \
		$(MAKE) -C $$i clean ; \
	done

distclean:
	if [ -e expat-2.1.0/Makefile ]; then \
		make -C expat-2.1.0 distclean; \
	fi
	if [ -e dbus-1.8.0/Makefile ]; then \
		make -C dbus-1.8.0  distclean; \
	fi
	if [ -e libusb-1.0.9/Makefile]; then \
		make -C libusb-1.0.9 distclean; \
	fi
	if [ -e libffi-3.0.13/Makefile ]; then \
		make -C libffi-3.0.13 distclean; \
	fi
	if [ -e gettext-0.18.3.1/Makefile ]; then \
		make -C gettext-0.18.3.1 distclean; \
	fi
	if [ -e glib-2.36.0/Makefile ]; then \
		make -C glib-2.36.0 distclean; \
	fi
	if [ -e bluez-4.96/Makefile ]; then \
		make -C bluez-4.96 distclean; \
	fi
	if [ -e libiconv-1.14/Makefile ]; then \
		make -C libiconv-1.14 distclean; \
	fi
	if [ -e alsa-lib-1.0.25/Makefile ]; then \
		make -C alsa-lib-1.0.25 distclean; \
	fi
	if [ -e zlib-1.2.8/Makefile ]; then \
		make -C zlib-1.2.8 distclean; \
	fi

prune:
	-for i in $(sort $(app_n) $(app_)) ; do \
		found=0; \
		for j in $(sort $(app_y)) ; do \
			if [ $$i = $$j ]; then \
				found=1; \
			fi; \
		done; \
	done

include Kconfig.mk
