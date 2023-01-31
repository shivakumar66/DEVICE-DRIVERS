obj-m :=new_driver.o 

KERNDIR=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default: 
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
	gcc -o read read.c
	gcc -o write1 write1.c
	gcc -o write2 write2.c  

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean 
	rm read write1 write2
	 
