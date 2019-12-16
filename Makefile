
all:
	make -f top.mk all

app: subinfo 
	make -f top.mk app

subinfo:
	make -f top.mk subinfo

kernel:
	make -f top.mk kernel

menuconfig:
	make -f top.mk menuconfig

clean:
	make -f top.mk clean



.PHONY: all app kernel menuconfig clean
