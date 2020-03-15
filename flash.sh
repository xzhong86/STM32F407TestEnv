#!/bin/sh
# usage: ../flash.sh app.elf

app=$1

cfg=openocd.cfg
if [ ! -e $cfg ] && [ -e ../openocd.cfg ] ; then
    cfg=../openocd.cfg
else
    echo "cfg not found"
    exit 1
fi

openocd -f $cfg -c "program $app ; exit"

