#!/bin/sh

ans=NULL

while [ "$ans" != "y" ] && [ "$ans" != "n" ]
do

echo "What will you enable or disable the keypad?[y/n]"
read ans
    
    if test "$ans" = "y" ; then
	echo "enabled keypad"
	xinput enable 13
    elif test "$ans" = "n"; then
	echo "disabled keypad"
	xinput disable 13
    else
	echo "Sorry, Wrong Word"
    fi
done
