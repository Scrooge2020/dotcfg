#!/bin/sh
# This is to be run just before suspend
# Pause all players, lock the screen and turn off the display
# Depends on: playerctl, xset, slock

export DISPLAY=:0
playerctl -a pause > /dev/null 2>&1
xset dpms force off
slock &
