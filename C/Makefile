objects = main.o getdata.o calc.o putdata.o
main:$(objects)
main.o:main.c getdata.h putdata.h calc.h define.h
getdata.o:getdata.c getdata.h define.h
calc.o:calc.c calc.h
putdata.o:putdata.c putdata.h
.PHONY:clean
clean:
	-rm $(objects)
	-rm main
