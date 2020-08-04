#!/bin/sh

echo 参考URL http://qiita.com/inohiro/items/5d358c30eb7bacb37c7c

echo sudo apt-get clean
sudo apt-get clean;

echo sudo apt-get autoremove
sudo apt-get autoremove;

echo Delete linux image
dpkg -l 'linux-*' | sed '/^ii/!d;/'"$(uname -r | sed "s/\(.*\)-\([^0-9]\+\)/\1/")"'/d;s/^[^ ]* [^ ]* \([^ ]*\).*/\1/;/[0-9]/!d' | xargs sudo apt-get -y purge;

echo Start BleachBit!!
sudo bleachbit
