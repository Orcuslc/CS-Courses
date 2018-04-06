#!/usr/bin/zsh
file=$1
mv /home/chuan/Downloads/$file.zip ./
unzip $file.zip
rm $file.zip
cd $file/

