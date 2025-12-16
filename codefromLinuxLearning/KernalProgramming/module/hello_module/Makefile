obj-m := hello.o

KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order



