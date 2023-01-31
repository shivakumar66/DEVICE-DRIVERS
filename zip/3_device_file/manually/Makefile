obj-m += char2.o
 
KERN_DIR_ARM=/lib/modules/5.15.84-v7l+/build/ 
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

ARM:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR_ARM) M=$(PWD) modules

 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

