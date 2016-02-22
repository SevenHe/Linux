#!/bin/bash
# Even though the constans is the number, need to be incorporated with quotes.
# This file is just in the /path/to/site.

Mgr='manage.py'
Dir=`pwd`
Site=`basename $Dir`
DATABASE='/etc/init.d/oracle-xe'
homedir=~

print_message()
{
	$DATABASE status > /dev/null 
	if [ $? != "0" ]; then
		$DATABASE start
	else
		case "$1" in 
			start)
				echo -e "\033[31mDatabase has been startup, so just runserver..\033[0m"
				;;
			port)
				echo -e "\033[32mDatabase has been startup, so just load the uwsgi file configuration..\033[0m"
				;;
			socket)
				echo -e "\033[33mDatabase has been startup, so just load the socket..\033[0m"
			;;
			# need to be as a root.
			# and the first to-do is \033[s,[u to print some useful message in the middle.
			stop)
				echo -e "Stop Database [ \033[31m..\033[0m ]"
				$DATABASE stop > /dev/null
				echo -ne "\033[1A \033[K"
				echo -e "Stop Database [ \033[32mOK\033[0m ]"
				echo -e "Stop uwsgi [ \033[31m..\033[0m ]"
				killall -s 9 uwsgi > /dev/null
				echo -ne "\033[1A \033[K"
				echo -e "Stop uwsgi [ \033[32mOK\033[0m ]"
				echo -e "Stop nginx [ \033[31m..\033[0m ]"
				/etc/init.d/nginx stop > /dev/null
				echo -ne "\033[1A \033[K"
				echo -e "Stop nginx [ \033[32mOK\033[0m ]"
				exitCode=$?
				;;
		esac
	fi
}

if [ -f $Mgr ] && [ $# = "0" ]; then
	$DATABASE status > /dev/null 
	print_message start
	python $Mgr runserver 0.0.0.0:9090

elif [ -f $Mgr ] && [ $# = "1" ]; then
	case "$1" in
		-m)
			python $Mgr migrate
			# Do not change the original file for different sites.
			;;
		-u)
			print_message port
			sed "s#~#$homedir#" < TMS.xml > TMS_temp.xml
			sed -i "s#%work_and_app%.sock#127.0.0.1:9090#" TMS_temp.xml
			ps aux | grep uwsgi > /dev/null 
			if test $? -eq 0; then
				killall -s 9 uwsgi > /dev/null 2>&1
			fi
			uwsgi --master -T -x TMS_temp.xml
			rm TMS_temp.xml
			;;
		-s|--stop)
			print_message stop
			rm TMS_temp.xml
			exit $exitCode
			;;
		--check)
			# To use AWK or sed when there are some variables.
			# if the variable has a slash, may use the double quotes.
			# But the way always in use is to manipulate the patter with another mark "#", it is more flexible.
			sed "s#~#$homedir#" < TMS.xml > TMS_temp.xml
			sed -i "s#%work_and_app%#$Dir/$Site#" TMS_temp.xml
			cat TMS_temp.xml
			rm TMS_temp.xml
			;;
		--socket)
			# Create a socket for use, so that the config file is not always loaded manually.
			# use a socket, you need to specify the wsgi.py file.
			print_message socket
			sed "s#~#$homedir#" < TMS.xml > TMS_temp.xml
			sed -i "s#%work_and_app%#$Dir/$Site#" TMS_temp.xml
			ps aux | grep uwsgi > /dev/null 
			if test $? -eq 0; then
				killall -s 9 uwsgi > /dev/null 2>&1
			fi
			uwsgi --master -T --socket $Site.sock --wsgi-file TMS_wsgi.py -x TMS_temp.xml
			;;
	esac
else
	echo "Something Wrong!"
fi
