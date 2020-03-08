# Commands

## open tty terminal
  * `screen /dev/tty* 9600`, exit with `C-a :`, then `quit`
    * restore session: `screen -r`
    * hot keys: 'C-a k' => kill window, 'C-a d' => detach screen
  * `serial-term` in emacs, exit with `C-c k`.

## Work with OpenOCD
  * `openocd -f openocd.cfg` open monitor server on localhost 4444.
    * connect command: `telnet localhost 4444`
    * flash command: `program gpio.elf`
    * gdb command: `arm-none-eabi-gdb -ex 'target ext localhost:3333' gpio.elf`
      - halt target before gdb connect to target
  * `openocd -f openocd.cfg -c "program gpio.elf ; exit"` one line flash.


## Work with st-flash
  * `st-flash write xxx.bin 0x8000000` to flash binary
  * `st-util -m` to start gdb server
  * `arm-none-eabi-gdb -ex 'target ext localhost:4242' gpio.elf` connect to target.

