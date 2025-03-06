KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
SRC_DIR := src
EXTRA_CFLAGS := -std=gnu99 -Wno-declaration-after-statement

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/$(SRC_DIR) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/$(SRC_DIR) clean
