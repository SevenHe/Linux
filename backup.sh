#!/bin/bash
make()
{
if ! [ -d ./files ] && ! [ -d ./backups ]; then
	mkdir ./files
	mkdir ./backups
fi
for i in {0..99}
do
	if ! [ -e ./files/a$i ] && [ $i -lt 10 ]; then
		touch ./files/a0$i
	elif [ $i -ge 10 ]; then
		touch ./files/a$i
	fi
done
if [ $? = "0" ]; then
	echo "Make files: [ OK ]"
fi
}

backup()
{
year=`date +%Y`
month=`date +%m`
day=`date +%d`
# take care of the path you are using.
for File in `ls ./files`
do
	if ! [ -f ./files/$File ]; then
		echo "File $File do not exist."
	else
		cp ./files/$File  ./backups/$File-$year-$month-$day
	fi
done
if [ $? = "0" ]; then
	echo "Backup successfully!"
fi
}

case "$1" in
	make)
		make
		;;
	backup)
		backup
		;;
esac 
exit $?
