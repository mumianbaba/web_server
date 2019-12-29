EXTRA_CFLAGS += -I./include -I./../api/include/


SRC	= $(wildcard ./src/*.c)
SRCPP = $(wildcard ./src/*.cpp)

ALL_OBJS = $(patsubst %.c, %.o, $(SRC))
ALL_OBJS += $(patsubst %.cpp, %.o, $(SRCPP))

ALL_D := $(patsubst %.o, %.d, $(ALL_OBJS))

ALL_EXE :=$(patsubst %.o, %, $(ALL_OBJS))

all:$(ALL_EXE)


$(ALL_EXE): $(ALL_OBJS)
	g++  $^ ./../api/api.o  -lpthread -o $@

%.o:%.c
	gcc -c $^ $(EXTRA_CFLAGS) -o $@

%.o:%.cpp
	g++ -c $^ $(EXTRA_CFLAGS) -o  $@

clean:
	rm $(MODULE) $(ALL_EXE) $(ALL_OBJS) $(ALL_D) -rf
