#!/bin/bash
PID=$(pgrep server | sed -n -e 1p)
kill -2 $PID
echo Killed server process with PID: $PID
PID=$(pgrep python | sed -n -e 1p)
kill -9 $PID
echo Killed python process with PID: $PID
