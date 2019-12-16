
export TOPDIR = $(PWD)

CONFIG_CLIENT = 1

ifneq ($(wildcard  $(TOPDIR)/.config),)
include $(TOPDIR)/.config
endif

MODEL_PATHS :=
MODELS := 

ifdef CONFIG_CLIENT
	export CLIENT_PATH := $(TOPDIR)/client

ifneq ($(wildcard $(CLIENT_PATH)/sub.mk),)
	include $(CLIENT_PATH)/sub.mk
endif
	MODELS += $(CLIENT)
	MODEL_PATHS += $(CLIENT_PATH)
endif



.PHONY: all app subinfo menuconfig clean

all: app
	echo "TOPDIR:${TOPDIR}"

app:
	@echo "make a app for you"
	make -C $(CLIENT_PATH)

subinfo:
	make -C $(CLIENT_PATH) subinfo


kernel:
	@echo "make a kernel for you"

menuconfig: Config.in
	@echo "make a menuconfig for you"
	./mconf Config.in

clean:
	@echo "clear all"
	rm -rf exe
	make -C $(CLIENT_PATH) clean


