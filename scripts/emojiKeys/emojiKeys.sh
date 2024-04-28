#!/bin/sh
# Depends on xdotool, dmenu

# Get user selection via dmenu from emoji file.
chosen=$(cut -d ';' -f1 ~/.local/share/emoji | dmenu -i -l 15 | sed "s/ .*//")

# Exit if none chosen.
[ -z "$chosen" ] && exit

xdotool type "$chosen"
