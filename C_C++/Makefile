sources1 = TCPServer.c
objects1 := $(patsubst %.c,%,$(sources1))
sources2 = TCPClient.c
objects2 := $(patsubst %.c,%,$(sources2))
sources3 = raw_socket.c
objects3 := $(patsubst %.c,%,$(sources3))
sources4 = FTPServer.cpp
sources5 = FTPClient.cpp
objects4 := $(patsubst %.cpp,%,$(sources4))
objects5 := $(patsubst %.cpp,%,$(sources5))
dbsources = test_mysql.cpp
dbobjects := $(patsubst %.cpp,%,$(dbsources))


objects := $(objects1) $(objects2) $(objects3)
CPPobjects := $(objects4) $(objects5)
DBobjects := $(dbobjects)

CPP = g++
FLAGS = -g -DDEBUG
LFLAGS = -lboost_system -lboost_thread -lpthread
DBFLAGS = -lmysqlcppconn

server:$(sources1)
client:$(sources2)
raw_socket:$(sources3)
FTPServer:$(sources4)
FTPClient:$(sources5)
db:test_mysql
test_mysql:$(dbsources)
$(objects): %: %.c
	$(CC) $(FLAGS) $< -o $@
$(CPPobjects): %: %.cpp
	$(CPP) $(FLAGS) $< -o $@ $(LFLAGS)
$(DBobjects): %: %.cpp
	$(CPP) $(FLAGS) $< -o $@ $(DBFLAGS) 
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

