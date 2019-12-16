
CONFIG_PERIPHERAL = 1
CONFIG_PERIPHERAL_LED = 1
CONFIG_PERIPHERAL_SLED = 1


include $(TOPDIR)/.config

TARGE := peripheral



ifdef CONFIG_PERIPHERAL

ifdef CONFIG_PERIPHERAL_LED
	PERIPHERAL := $(PERIPHERAL_PATH)/led/led.o
endif

ifdef CONFIG_PERIPHERAL_SLED
	PERIPHERAL += $(PERIPHERAL_PATH)/sled/sled.o
endif

ifdef CONFIG_PERIPHERAL_SWRST_KEY
	PERIPHERAL += $(PERIPHERAL_PATH)/key/key.o
else
ifdef CONFIG_PERIPHERAL_CHANNEL_KEY
	PERIPHERAL += $(PERIPHERAL_PATH)/key/key.o
else
ifdef CONFIG_PERIPHERAL_MODE_KEY
	PERIPHERAL += $(PERIPHERAL_PATH)/key/key.o
endif  #mode_key
endif  #channel_key
endif  #swrst_key

endif  #peripheral


PERIPHERAL_SUBPATH := $(foreach n, $(PERIPHERAL), $(dir $(n)))


.PHONY: all $(TARGE)  subinfo clean


XLD = $(CROSS_PREFIX)ld


all: $(TARGE)
	@echo "create a peripheral.o"
	$(XLD) -r -o $(TARGE).o $(PERIPHERAL)

$(TARGE):
	@echo "make $(TARGE) for you"
	@for var in $(PERIPHERAL_SUBPATH);do \
		make -C $$var; \
	done


subinfo:
	@echo "create sub.mk"
	@echo "export PERIPHERAL_SUBPATH += $(PERIPHERAL_SUBPATH)" > sub.mk 


clean:
	@echo "clear $(TARGE)"
	rm $(TARGE).o sub.mk -rf 
	@for var in $(PERIPHERAL_SUBPATH);do \
		make -C $$var clean; \
	done

