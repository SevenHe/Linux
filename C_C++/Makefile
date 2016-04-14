sources1 = TCPServer.c
objects1 := $(patsubst %.c,%,$(sources1))
sources2 = TCPClient.c
objects2 := $(patsubst %.c,%,$(sources2))
sources3 = raw_socket.c
objects3 := $(patsubst %.c,%,$(sources3))
objects := $(objects1) $(objects2) $(objects3)
FLAGS = -g
server:$(sources1)
client:$(objects2)
raw_socket:$(sources3)
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
	-@echo "clean test!!"

