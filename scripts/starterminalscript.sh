#!/bin/bash

case "$1" in
    start)
        kitty cava; sleep 2; kitty tty-clock -s -c
        ;;
    music)
        chromium --kiosk --disable-infobars $2
        ;;
    *)
        echo "404"
        ;;
esac