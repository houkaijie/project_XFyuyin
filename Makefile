#
# Makefile
#-L/home/gec/freetype-2.12.1/tmp/lib -I/home/gec/freetype-2.12.1/tmp/include/freetype2
CC = arm-linux-gcc
CXX = arm-linux-g++

LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -O3 -g0   -I$(LVGL_DIR)/ -I/home/gec/usr/local/include/freetype2 -Wall  -std=gnu99
CXXFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ -I./login/ -I./smartClass/ -I/home/gec/usr/local/include/freetype2 -Wall -std=c++11  # 添加 C++ 编译选项
LDFLAGS ?= -L/home/gec/usr/local/lib -lm -lz -lfreetype -lpthread
BIN = demo


#Collect the files to compile
MAINSRC = ./main.c 
CSRC = ./clientWav/client_wav.c
#OTHERSRC = ./lvgl/examples/libs/png/lv_example_png_1.c ./lvgl/examples/libs/freetype/lv_example_freetype_1.c
CXXSRC = ./login/login.cpp ./smartClass/src/Bmp.cpp ./smartClass/src/Mp3Mp4.cpp ./smartClass/src/Theard.cpp ./smartClass/src/LedBeep.cpp
# ./smartClass/include/other.cpp 
include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT)) $(CSRC:.c=$(OBJEXT))
CXXOBJS = $(CXXSRC:.cpp=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))
# OTHEROBJ = $(OTHERSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC) $(CXXSRC) $(CSRC)
OBJS = $(AOBJS) $(COBJS) $(CXXOBJS) $(MAINOBJ)

## MAINOBJ -> OBJFILES


all: default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "CXX $<"
    
default: $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

clean: 
	rm -f $(BIN) $(OBJS) 

