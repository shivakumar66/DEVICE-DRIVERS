obj-m:= wq.o

Kern_Dir = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

default:
	make -C $(Kern_Dir) M=$(PWD) modules

clean:
	make -C $(Kern_Dir) M=$(PWD) clean