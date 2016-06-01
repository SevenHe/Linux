srcs = $(wildcard *.cpp)
objs = $(patsubst %.cpp,%.o,$(srcs))
exc = query

CPP = g++
CPFLAGS = -g -Wall

query:$(objs)
	$(CPP) $(objs) -o $(exc)

$(objs): %.o: %.cpp
	$(CPP) $(CPFLAGS) -c $<  

.PHONY:data-clean
data-clean:
	-rm indexes/*
