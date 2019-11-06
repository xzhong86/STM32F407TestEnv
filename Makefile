# zpzhong, stm32 simple project

PREFIX = $(HOME)/local/bin/arm-none-eabi-

ST_FLASH = $(HOME)/local/bin/st-flash

# stm32f103c8t6
#MCU = STM32F103xB
# stm32f401ccub
#MCU = STM32F401xC
# stm32f407vet6
MCU = STM32F407xx

CUBE_ROOT    = $(HOME)/work/geek/stm32/stm32cube/STM32Cube_FW_F4_V1.24.0
CUBE_DRIVER  = $(CUBE_ROOT)/Drivers
CUBE_PROJECT = $(CUBE_ROOT)/Projects/STM32F4-Discovery/Templates
STM32_TYPE   = STM32F4xx
#startup.s = $(CUBE_PROJECT)/SW4STM32/startup_stm32f401xc.s
#system.c  = $(CUBE_PROJECT)/Src/system_stm32f4xx.c
startup.s = $(CUBE_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
system.c  = $(CUBE_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
ld-script = $(CUBE_PROJECT)/SW4STM32/STM32F4-Discovery/STM32F407VGTx_FLASH.ld

hal_src   = $(CUBE_DRIVER)/$(STM32_TYPE)_HAL_Driver/Src
hal_objs  = $(patsubst $(hal_src)/%.c,hal_objs/%.o,$(wildcard $(hal_src)/*.c))
hal_objs := $(filter-out %template.o, $(hal_objs))
libhal    = hal_objs/libhal.a

CUBE_INC  = -I$(CUBE_DRIVER)/$(STM32_TYPE)_HAL_Driver/Inc
CUBE_INC += -I$(CUBE_DRIVER)/CMSIS/Device/ST/$(STM32_TYPE)/Include
CUBE_INC += -I$(CUBE_DRIVER)/CMSIS/Include
CUBE_INC += -I$(CUBE_PROJECT)/Inc

com_objs = objs/startup.o objs/system.o
#src_objs = $(patsubst src/%.c,objs/%.o,$(wildcard src/*.c))
src_objs = objs/main.o objs/syscalls.o objs/stm32f4xx_it.o

#CFLAGS += -mcpu=cortex-m3 -mthumb -D$(MCU)
CFLAGS += -mcpu=cortex-m4 -mthumb -D$(MCU)
CFLAGS += $(CUBE_INC) -I./src
CFLAGS += -Os -O2 -g

BIN = gpio.bin

all: _mkdir gpio.elf

objs/startup.o : $(startup.s)
	$(PREFIX)gcc $(CFLAGS) -c -o $@ $<
objs/system.o : $(system.c)
	$(PREFIX)gcc $(CFLAGS) -c -o $@ $<

gpio.elf : $(com_objs) $(src_objs) $(libhal)
	$(PREFIX)gcc $(CFLAGS) -T $(ld-script) -o $@ $^

$(libhal) : $(hal_objs)
	$(PREFIX)ar -r $@ $^

hal_objs/%.o : $(hal_src)/%.c
	$(PREFIX)gcc $(CFLAGS) -c -o $@ $<

objs/%.o : src/%.c
	$(PREFIX)gcc $(CFLAGS) -c -o $@ $<

%.dump : %.elf
	$(PREFIX)objdump -D $< > $@

%.bin : %.elf
	$(PREFIX)objcopy -O binary $< $@

.PHONY: clean flash link
clean:
	rm -rf objs/ hal_objs/ *.elf *.bin *.dump
_mkdir:
	mkdir -p objs hal_objs

flash: $(BIN)
	$(ST_FLASH) write $(BIN) 0x8000000

link:   # to view source code
	ln -s $(CUBE_DRIVER)/$(STM32_TYPE)_HAL_Driver HAL_Driver
	ln -s $(CUBE_ROOT)/Drivers/CMSIS CMSIS
	ln -s $(startup.s)

# start gdb server: st-util -m
# start gdb: arm-none-eabi-gdb gpio.elf
# connect:   (gdb) target ext localhost:4242

