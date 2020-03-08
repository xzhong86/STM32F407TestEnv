# -*- makefile-gmake -*-
# zpzhong, stm32 simple project

# stm32f407vet6
MCU = STM32F407xx

#src_objs = $(patsubst src/%.c,objs/%.o,$(wildcard src/*.c))
src_objs = objs/main.o objs/syscalls.o objs/irq_handlers.o objs/stm32f4xx_hal_msp.o

CFLAGS += -mcpu=cortex-m4 -mthumb -D$(MCU)
CFLAGS += -I./src -Os -O2 -g

TARGET = gpio.elf

include Makefile.common
include Makefile.cube



# start gdb server: st-util -m
# start gdb: arm-none-eabi-gdb gpio.elf
# connect:   (gdb) target ext localhost:4242

