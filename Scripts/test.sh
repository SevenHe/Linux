#!/bin/zsh
# "=" is the judgement mark.
if [ "`echo 'ok' | wc -l`" = "1" ]
then
	echo "OK!!"
fi
if [ "`echo "LKJSDFKJLA" | tr A-Z a-z`" = "true" ]
then
	echo "test OK!!"
fi
