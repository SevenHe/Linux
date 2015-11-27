#!/bin/bash
# Even though the constans is the number, need to be incorporated with quotes.

Mgr='manage.py'
if [ -f $Mgr ] && [ $# = "0" ]; then
	python $Mgr runserver 0.0.0.0:9090
elif [ -f $Mgr ] && [ $# = "1" ] && [ $1 = "-m" ]; then
	python $Mgr migrate
elif [ -f $Mgr ] && [ $# = "1" ] && [ $1 = "-u" ]; then
	uwsgi --master -x HelloWorld.xml
else
	echo "Something Wrong!"
fi