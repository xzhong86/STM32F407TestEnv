# -*- makefile-gmake -*-
# zpzhong, makefile template

ROOT ?= ..
USE_CMSIS_RTOS = yes

MCU = STM32F407xx

#src_objs = main.o stm32f4xx_it.o stm32f4xx_hal_timebase_tim.o
src_objs = main.o stm32f4xx_it.o 
#src_objs = $(patsubst %.c,objs/%.o,$(wildcard *.c))

CFLAGS += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -D$(MCU)
#CFLAGS += -mcpu=cortex-m4 -D$(MCU)
CFLAGS += -I. -Os -O2 -g

TARGET = app.elf

include $(ROOT)/Makefile.common
include $(ROOT)/Makefile.cube


