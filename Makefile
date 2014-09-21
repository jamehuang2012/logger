CC      := gcc
LD      := ld
LDFLAGS := -shared -fPIC -lrt

TOP =..
OBJS =  logger.o queue.o
TARGET:= liblogger.so



CFLAGS += -I$(TOP)/include
CFLAGS += -I$(TOP)/src
CFLAGS += -pthread -D_GNU_SOURCE
CFLAGS += $(INCLUDE_PATH)
CFLAGS += -fPIC
# Default architecture is x86
ARCH ?= x86

ifeq ($(ARCH),arm)
CFLAGS += -mtune=cortex-a8
CFLAGS += -mfpu=neon
CFLAGS += -ftree-vectorize
CFLAGS += -mfloat-abi=softfp
CFLAGS += -mcpu=arm9
CFLAGS += -DSCU_BUILD
CC=arm-none-linux-gnueabi-gcc
CXX=arm-none-linux-gnueabi-g++
LD=arm-none-linux-gnueabi-ld

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
                                      
