#!/bin/sh
# Simple Wrapper Script for iwd-iwctl
# This is mostly in case I forget the commands and there's no internet

IFACE="wlan0"

getinfo()
{
	iwctl station "${IFACE}" show
}

scan()
{
	iwctl station "${IFACE}" scan
	iwctl station "${IFACE}" get-networks
}

connect()
{
	checkArgs
	iwctl station "${IFACE}" connect "${arg2}"
}

disconnect()
{
	iwctl station "${IFACE}" disconnect
}

listKnownNetworks()
{
	iwctl known-networks list
}

disableAutoConnect()
{
	checkArgs
	iwctl known-networks "${arg2}" set-property AutoConnect no
}

forget()
{
	checkArgs
	iwctl known-networks "${arg2}" forget
}

checkArgs()
{
	if [ -z "${arg2}" ]; then
		error
	fi
}

off()
{
	disconnect
	rfkill block wifi
}

on()
{
	rfkill unblock wifi
	sleep 1
	scan
}

error()
{
	scriptname="$(basename "$0")"
	echo "Usage: ${scriptname} [-s] | [-c network] | [-d] | [-k] | [-a network] | [-f network] | on | off"
	exit 1
}

arg1="${1}"
arg2="${2}"

if [ -z "${arg1}" ]; then
	getinfo
else
	case "${arg1}" in
		"-s") scan
			;;
		"-c") connect
			;;
		"-d") disconnect
			;;
		"-k") listKnownNetworks
			;;
		"-a") disableAutoConnect
			;;
		"-f") forget
			;;
		"on") on
			;;
		"off") off
			;;
		   *) error
			;;
	esac
fi
