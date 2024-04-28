#!/bin/sh
# dsess.sh (DWM Session Script)
# It periodically updates the DWM status Bar and autolocks the screen if nothing is playing
# Depends on: alsa-utils, xsetroot, xset, xssstate, slock

get_wifi_stat()
{
	if grep -q 'up' '/sys/class/net/wlan0/operstate'; then
		SIGDBM="$(awk '/wlan0/ {print substr($4, 1, length($4)-1)}' '/proc/net/wireless')"
		if [ -z "${SIGDBM}" ]; then
			echo '*'
		elif [ "${SIGDBM}" -le -80 ]; then
			echo '1'
		elif [ "${SIGDBM}" -le -66 ]; then
			echo '2'
		elif [ "${SIGDBM}" -le -56 ]; then
			echo '3'
		elif [ "${SIGDBM}" -le -47 ]; then
			echo '4'
		elif [ "${SIGDBM}" -gt -47 ]; then
			echo '5'
		else
			echo '*'
		fi
	else
		echo '*'
	fi
}

update_stats()
{
	VOLUME="$(amixer sget Master | awk -F'[][]' '/Mono:/ { print $2 }')"
	WIFI="$(get_wifi_stat)"
	DATETIME="$(date '+%a, %d %b %H:%M')"

	xsetroot -name " 🌐:$WIFI | 🔈:$VOLUME | ⏰:$DATETIME "
}

run_autolock()
{
	XSSOUT="$(xssstate -t)"
	if ! grep -q 'running' '/proc/asound/timers'; then
		if [ "$(pgrep -fc slock)" -eq 0 ] && [ "${XSSOUT}" -le $((REFRESHTIME * 1000)) ] && [ "${XSSOUT}" -ge 0 ]; then
			slock
		fi
		xset s on
	else
		xset s off
	fi
}

run_as_daemon()
{
	if [ "$(pgrep -fc "${0}")" -gt 1 ]; then
		echo "${0}"" Already running in Daemon mode."
		exit 1
	fi

	while true; do
		run_autolock
		update_stats
		sleep "${REFRESHTIME}"
	done
}

# Main ------------------------|

if [ -z "$DISPLAY" ]; then
	echo "X-server Not Running."
	exit 1
fi

case $1 in
	-d) REFRESHTIME=10
		run_as_daemon;;
	*) update_stats;;
esac
