#/bin/bash

set -e
#$1 is the name of the intput file (iml file)
#s2 is the name of the output file (executable)

echo "Eaglecompiler > /tmp/out.asm... "
../../cmake/EagleCompiler/EagleCompiler > /tmp/out.asm
echo "------------------"
cat -n /tmp/out.asm
echo "------------------"
echo "Done"

#!/bin/bash
if [ "$(uname)" == "Darwin" ]
then
  os=macho
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]
then
  os=elf
fi

echo "nasm > /tmp/out.o... "
nasm /tmp/out.asm -o /tmp/out.o -f $os
echo "Done"
echo "gcc > "$2"... "
gcc -m32 /tmp/out.o -o $2
echo "Done"
echo "All done, Executable is "$2
