sources1 = TCPServer.c
objects1 := $(patsubst %.c,%,$(sources1))
sources2 = TCPClient.c
objects2 := $(patsubst %.c,%,$(sources2))
objects := $(objects1) $(objects2)
FLAGS = -g
server:$(objects1)
client:$(objects2)
$(objects): %: %.c
	$(CC) $(FLAGS) $< -o $@
#sinclude $(sources:.c=.d)
#%.d:%.c
#	...;\
#	...;\
#	...
#main.o:main.c getdata.h putdata.h calc.h define.h
#getdata.o:getdata.c getdata.h define.h
#calc.o:calc.c calc.h
#putdata.o:putdata.c putdata.h
.PHONY:clean
clean:
	-rm main

