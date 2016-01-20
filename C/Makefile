sources = main.c getdata.c calc.c putdata.c
objects := $(patsubst %.c,%.o,$(sources))
main:$(objects)
#sinclude $(sources:.c=.d)
#%.d:%.c
#	...;\
#	...;\
#	...
main.o:main.c getdata.h putdata.h calc.h define.h
getdata.o:getdata.c getdata.h define.h
calc.o:calc.c calc.h
putdata.o:putdata.c putdata.h
.PHONY:clean
clean:
	-rm $(objects)
	-rm main
