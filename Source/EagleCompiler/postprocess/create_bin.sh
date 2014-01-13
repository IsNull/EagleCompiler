#!/bin/bash

set -e
#$1 is the name of the intput file (asm file)
#s2 is the name of the output file (executable)

#echo "Eaglecompiler > /tmp/out.asm... "
#../../cmake/EagleCompiler/EagleCompiler > /tmp/out.asm
#echo "------------------"
#cat -n /tmp/out.asm
#echo "------------------"
#echo "Done"

if [ "$(uname)" == "Darwin" ]
then
  os=macho
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]
then
  os=elf
fi

echo "Generate objectcode from assembler-file "$1"... "
nasm $1 -o /tmp/out.o -f $os -g
echo "Linking executable "$2"... "
gcc -O0 -g -m32 /tmp/out.o -o $2
rm /tmp/out.o
echo "Done"
