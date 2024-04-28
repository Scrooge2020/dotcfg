#!/bin/sh
# This is to change the orientation of Wacom Tablet based on usage
# W A S D -> this is to point where the wire is connected
# Simple Wrapper - Depends on xf86-input-wacom

device1='Wacom One by Wacom M Pen stylus'
device2='Wacom One by Wacom M Pen eraser'

case "${1}" in
	"-w") xsetwacom set "${device1}" Rotate ccw
		  xsetwacom set "${device2}" Rotate ccw
		;;
	"-a") xsetwacom set "${device1}" Rotate none
		  xsetwacom set "${device2}" Rotate none
		;;
	"-s") xsetwacom set "${device1}" Rotate cw
		  xsetwacom set "${device2}" Rotate cw
		;;
	"-d") xsetwacom set "${device1}" Rotate half
		  xsetwacom set "${device2}" Rotate half
		;;
	   *) scriptname="$(basename "$0")"
	      echo "Usage: ${scriptname} [-w | -a | -s | -d]"
		;;
esac
