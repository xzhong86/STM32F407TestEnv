# -*- makefile-gmake -*-
# zpzhong, makefile template

ROOT ?= ..

MCU = STM32F407xx

srcs = init_gpio.c irq_handlers.c main.c
src_objs = $(patsubst %.c,objs/%.o,$(srcs))

CFLAGS += -mcpu=cortex-m4 -mthumb -D$(MCU)
CFLAGS += -I. -Os -O2 -g

TARGET = app.elf

include $(ROOT)/Makefile.common
include $(ROOT)/Makefile.cube


