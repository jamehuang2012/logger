#CC=arm-none-linux-gnueabi-gcc
#CXX=arm-none-linux-gnueabi-g++


EXE=test

#SOURCES = font_8x16.c font_8x8.c  fbutils.c
OBJECTS=logger.o queue.o main.o
INCLUDE=-I/usr/include/lua5.1
LDFLAGS= -lrt -lpthread
#CFLAGS += -g -DDEBUG

.SUFFIXES: .o .c .cpp .cc .cxx .C
all:$(EXE) disclean

$(EXE):$(OBJECTS)
	$(CC) $^ $(INCLUDE) -o $@ $(LDFLAGS)
.cpp.o:
	$(CXX) -c $(INCLUDE) -o "$@" "$<"
	
.c.o:
	$(CC) -c $(INCLUDE) -o "$@" "$<" $(CFLAGS)
	

.PHONY :disclean
disclean:
	-rm -rf *.o	
clean:
	-rm -rf *.o $(EXE)
