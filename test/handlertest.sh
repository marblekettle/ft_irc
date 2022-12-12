#!/bin/bash
make -C..
rm ../obj/main.o
c++ -I../include ../obj/*.o testhandler.cpp -o handlertest
make -C.. clean
while read line; do
	echo "[$line]"
	./handlertest "$line"
done < lines.txt
rm handlertest