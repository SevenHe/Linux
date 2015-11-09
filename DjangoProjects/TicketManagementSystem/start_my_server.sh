#!/bin/bash
# Even though the constans is the number, need to be incorporated with quotes.

Mgr='manage.py'
DATABASE='/etc/init.d/oracle-xe'
if [ -f $Mgr ] && [ $# = "0" ]; then
	$DATABASE status > /dev/null 
	if [ $? != "0" ]; then
		$DATABASE start
	else
		echo "Database has been startup, so just runserver..\n"
	fi
	python $Mgr runserver 0.0.0.0:9090

elif [ -f $Mgr ] && [ $# = "1" ] && [ $1 = "-m" ]; then
	python $Mgr migrate
elif [ -f $Mgr ] && [ $# = "1" ] && [ $1 = "-u" ]; then
	$DATABASE status > /dev/null 
	if [ $? != "0" ]; then
		$DATABASE start
	else
		echo "Database has been startup, so just runserver..\n"
	fi
	uwsgi --master -x TMS.xml
else
	echo "Something Wrong!"
fi
