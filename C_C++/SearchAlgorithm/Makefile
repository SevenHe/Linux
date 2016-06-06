srcs = $(wildcard *.cpp)
src = index_detect.cpp
search_index = search.cpp
query = query.cpp cluster.cpp
srcs1 = $(src) $(query)
srcs2 = $(src) $(search_index)
heads = cluster_config.h
objs = $(patsubst %.cpp,%.o,$(srcs))
objs1 = $(patsubst %.cpp,%.o,$(srcs1))
objs2 = $(patsubst %.cpp,%.o,$(srcs2))
exc1 = query
exc2 = update

CPP = g++
CPFLAGS = -g -Wall

query:$(objs1)
	$(CPP) $(objs1) -o $(exc1)

update:$(objs2)
	$(CPP) $(objs2) -o $(exc2)

$(objs): %.o: %.cpp
	$(CPP) $(CPFLAGS) -c $<  

.PHONY:data-clean
data-clean:
	-rm indexes/*
