#$1 is the name of the intput file (assembler file)
#s2 is the name of the output file (executable)

#!/bin/bash
if [ "$(uname)" == "Darwin" ]
then
  os=macho32
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]
then
  os=elf32
fi
#For 64-bit binary code, remove "--32"
nasm $1 -o $1".o" -f $os 
#For 64-bit executable remove "-m elf_i386"
ld -s $1".o" -o $2 -m elf_i386 
rm $1".o" 2>/dev/null
