# STM32F4 Test Env Project

  ARM GCC compile environment without IDE. Licnese GPLv3.

  You can get more details from Makefile.


## Requirement:
  * toolchain: arm-none-eabi-, [Link](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  * HAL Driver: STM32 Cube Library (download from st.com or [GitHub](https://github.com/STMicroelectronics/STM32CubeF4)).
  * flash & debug: stlink, openocd 


## My board:
  * FK407M1 with stm32f407VET6 on board from taobao.com.


## Commands:

  Frequency Used Command for me. (I work on a MacBookPro)

### open tty terminal
  * `screen /dev/tty* 9600`, exit with `C-a :`, then `quit`
    * restore session: `screen -r`
    * hot keys: 'C-a k' => kill window, 'C-a d' => detach screen
  * `serial-term` in emacs, exit with `C-c k`.

### Work with OpenOCD
  * `openocd -f openocd.cfg` open monitor server on localhost 4444.
    * connect command: `telnet localhost 4444`
    * flash command: `program gpio.elf`
    * gdb command: `arm-none-eabi-gdb -ex 'target ext localhost:3333' gpio.elf`
      - halt target before gdb connect to target
  * `openocd -f openocd.cfg -c "program gpio.elf ; exit"` one line flash.


### Work with st-flash
  * `st-flash write xxx.bin 0x8000000` to flash binary
  * `st-util -m` to start gdb server
  * `arm-none-eabi-gdb -ex 'target ext localhost:4242' gpio.elf` connect to target.

