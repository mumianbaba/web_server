CONFIG_CLIENT = 1
CONFIG_CLIENT_API = 1


include $(TOPDIR)/.config

TARGE := client

ifdef CONFIG_CLIENT

ifdef CONFIG_CLIENT_API
	CLIENT := $(CLIENT_PATH)/api/api.o
endif

endif

CLIENT_SUBPATH := $(foreach n, $(CLIENT), $(dir $(n)))


.PHONY: all $(TARGE)  subinfo clean


XLD = $(CROSS_PREFIX)ld


all: $(TARGE)
	@echo "create a client.o"
	$(XLD) -r -o $(TARGE).o $(CLIENT)

$(TARGE):
	@echo "make $(TARGE) for you"
	@for var in $(CLIENT_SUBPATH);do \
		make -C $$var; \
	done


subinfo:
	@echo "create sub.mk"
	@echo "export CLIENT_SUBPATH += $(CLIENT_SUBPATH)" > sub.mk 


clean:
	@echo "clear $(TARGE)"
	rm $(TARGE).o sub.mk -rf 
	@for var in $(CLIENT_SUBPATH);do \
		make -C $$var clean; \
	done

