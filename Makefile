# -*- makefile-gmake -*-
# zpzhong, makefile template

ROOT ?= ..

MCU = STM32F407xx

src_objs = $(patsubst %.c,objs/%.o,$(wildcard *.c))

CFLAGS += -mcpu=cortex-m4 -mthumb -D$(MCU)
CFLAGS += -I. -Os -O2 -g

TARGET = app.elf

include $(ROOT)/Makefile.common
include $(ROOT)/Makefile.cube


