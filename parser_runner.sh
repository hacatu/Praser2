#!/bin/sh
if [ ! -f lib/lib$1_parser.so ]
then
	echo "lib/lib$1_parser.so does not exist"
	exit 1
fi
if [ ! -f lib/libast_callback_$2.so ]
then
	echo "lib/libast_callback_$2.so does not exist"
	exit 1
fi
LD_PRELOAD="lib/libast_callback_$2.so lib/lib$1_parser.so" bin/parser_runner ${@:3}

