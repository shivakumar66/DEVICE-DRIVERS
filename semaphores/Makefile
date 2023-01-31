obj-m:= sem_driver.o

KD = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	make -C $(KD) M=$(PWD) modules
	gcc -o read read_app.c
	gcc -o write1 write_aap1.c
	gcc -o write2 write_app2.c

clean:
	make -C $(KD) M=$(PWD) clean
	rm -rf read write1 write2
