#
# Makefile for the enhance features modules on top of net
#
 
include $(DIR_ROOT)/.config

#EXTRA_CFLAGS += -I $(DIR_LINUX)/drivers/net/rtl819x
EXTRA_CFLAGS += -I $(DIR_LINUX)/net
EXTRA_CFLAGS += -D__KERNEL__
#EXTRA_CFLAGS += -Wno-implicit -Werror
 
ifeq "$(CONFIG_MODEL_RTL89xxC_SDK)" "y"
EXTRA_CFLAGS += --save-temps
endif
 
#EXTRA_CFLAGS += -DCONFIG_RTK_IPTABLES_FAST_PATH
#EXTRA_CFLAGS += -DCONFIG_FAST_PATH_MODULE

ifeq ($(CONFIG_RTL_819XD),y)
TARGET = 9xD
endif

ifeq ($(CONFIG_RTL_8196E),y)
TARGET = 96E
endif

ifeq ($(CONFIG_RTL_8881A),y)
TARGET = 9xD
endif
 
EFEATURES_OBJ=rtl_features.o rtl_ps_hooks.o
obj-y := $(EFEATURES_OBJ)
obj-$(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW) += $(TARGET)/rtl_nf_connGC.o
#obj-$(CONFIG_RTL_FASTBRIDGE) += fast_bridge.o
 
clean:
	rm -rf *.o *.ko *.mod.c
 
EXTRA_AFLAGS += $(EXTRA_CFLAGS)
