#!/bin/bash
PID=$(pgrep python | sed -n -e 1p)
kill -2 $PID
echo Killed python process with PID: $PID
