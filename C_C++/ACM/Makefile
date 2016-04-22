DIR2 = c2
DIR3 = c3
DIR4 = c4
source2 = $(wildcard $(DIR2)/*.c)
object2 = $(patsubst %.c,%,$(source2)) 
objects := $(object2)
source3 = $(wildcard $(DIR3)/*.c)
object3 = $(patsubst %.c,%,$(source3))
source4 = $(wildcard $(DIR4)/*.c)
object4 = $(patsubst %.c,%,$(source4))
objects += $(object3)
objects += $(object4)

CFLAGS = -g -Wall
LFLAGS = -lm

# implicit rules, just for %.c to %.o, not for %
# so here, use explicit rules
# $<, just the first dependency file, so need to use wildcards
acm2:$(object2)
acm3:$(object3)
acm4:$(object4)
$(objects): %: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

.PHONY:clean
clean:
	-@echo "clean test!"
