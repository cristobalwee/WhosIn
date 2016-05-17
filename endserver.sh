#!/bin/bash
PID=$(pgrep server | sed -n -e 1p)
kill -2 $PID
echo Killed server process with PID: $PID
