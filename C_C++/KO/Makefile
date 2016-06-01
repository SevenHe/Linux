sources := $(notdir $(wildcard $(PWD)/hello-[1-9].c))
#sources += $(notdir $(wildcard $(PWD)/*.c))
obj-m += $(patsubst %.c,%.o,$(sources))
obj-m += test.o
obj-m += chardev.o procfs1.o procfs2.o sleep.o
obj-m += print_string.o kbleds.o sched.o intrpt.o
test-objs := start.o stop.o
KMDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KMDIR) M=$(PWD) modules

test:
	@echo $(sources)
	@echo $(obj-m)

.PHONY:clean
clean:
	make -C $(KMDIR) M=$(PWD) clean 
