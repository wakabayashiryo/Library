#!/bin/sh

while true;do
	clear
	
	vcgencmd measure_temp
	vcgencmd measure_clock arm
	vcgencmd measure_volts
	vcgencmd get_mem arm
	vcgencmd get_mem gpu
	
	sleep 10
done


