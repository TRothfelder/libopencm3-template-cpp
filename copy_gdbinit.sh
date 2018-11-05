#!/usr/bin/env bash

FILE=~/.gdbinit.bak
if [ ! -f $FILE ]; then
   cp ~/.gdbinit $FILE
fi

cp gdbinit_generated ~/.gdbinit

