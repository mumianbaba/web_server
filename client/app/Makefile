include $(TOPDIR)/.config


EXTRA_CFLAGS += -I./include


SRC	= $(wildcard ./src/*.c)
SRCPP = $(wildcard ./src/*.cxx)

ALL_OBJS = $(patsubst %.c, %.o, $(SRC))
ALL_OBJS += $(patsubst %.cxx, %.o, $(SRCPP))

ALL_D := $(patsubst %.o, %.d, $(ALL_OBJS))

MODULE = $(shell pwd | sed "s/.*\///" ).o

all:$(MODULE)
	echo "ALL_OBJS:$(ALL_OBJS)"

include $(TOPDIR)/rules.mak

$(MODULE): $(ALL_OBJS) $(ALL_OBJS:.o=.d)
	$(XLD) -r $(ENDIAN) -o $(MODULE) $(ALL_OBJS)

clean:
	rm $(MODULE) $(ALL_OBJS) $(ALL_D) -rf


