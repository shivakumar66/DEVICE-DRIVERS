obj-m += driver2.o
 
ifdef ARCH
	#You can update your Beaglebone path here.
	KDIR = /home/embetronicx/BBG/tmp/lib/modules/5.10.65/build
else
	KDIR = /lib/modules/$(shell uname -r)/build
endif
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -o app app.c
	gcc -o app1 app1.c
	gcc -o app3 app3.c
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	rm -rf app
	rm -rf app1
	rm -rf app3
