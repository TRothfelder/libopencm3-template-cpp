#!/usr/bin/env bash

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

COMMAND="openocd -f $SCRIPTPATH/jlink.cfg -s $SCRIPTPATH"
echo $COMMAND
$COMMAND
