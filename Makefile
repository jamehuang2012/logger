CC      := gcc
LD      := ld
LDFLAGS := -shared -fpic -lrt 

TOP =..
OBJS =  logger.o queue.o 
TARGET:= liblogger.so
ARCH=arm


CFLAGS += -I$(TOP)/include
CFLAGS += -I$(TOP)/src
CFLAGS += -pthread -D_GNU_SOURCE
CFLAGS += $(INCLUDE_PATH)
#CFLAGS += -fPIC
# Default architecture is x86
ARCH ?= x86

ifeq ($(ARCH),arm)
CFLAGS += -mtune=cortex-a8
CFLAGS += -mfpu=neon
CFLAGS += -ftree-vectorize
CFLAGS += -mfloat-abi=softfp
CFLAGS += -mcpu=arm9
CFLAGS += -DSCU_BUILD
endif



all:$(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) 

%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)  

.PHONY:clean

clean:  
	@rm *.so *.o -rf

.PHONY:intall
install:
	@cp $(TARGET) /usr/scu/libs
                                      
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
