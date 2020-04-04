# -*- makefile-gmake -*-
# zpzhong, makefile template

ROOT ?= ..
USE_CUBE_USBH = yes

MCU = STM32F407xx

srcs  = main.c menu.c stm32f4xx_it.c usbh_conf.c
srcs += $(wildcard usbh_*.c)
#srcs += system_stm32f4xx.c

#src_objs = $(patsubst %.c,objs/%.o,$(wildcard *.c))
src_objs = $(patsubst %.c,objs/%.o,$(srcs))

CFLAGS += -mcpu=cortex-m4 -mthumb -D$(MCU)
CFLAGS += -I. -Os -O2 -g

TARGET = app.elf

include $(ROOT)/Makefile.common
include $(ROOT)/Makefile.cube


