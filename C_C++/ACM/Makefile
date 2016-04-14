DIR2 = c2
DIR3 = c3
source2 = $(wildcard $(DIR2)/*.c)
object2 = $(patsubst %.c,%,$(source2)) 
objects := $(object2)
source3 = $(wildcard $(DIR3)/*.c)
object3 = $(patsubst %.c,%,$(source3))
objects += $(object3)

CFLAGS = -g -Wall

# implicit rules, just for %.c to %.o, not for %
# so here, use explicit rules
# $<, just the first dependency file, so need to use wildcards
acm2:$(object2)
acm3:$(object3)
$(objects): %: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	-@echo "clean test!"
