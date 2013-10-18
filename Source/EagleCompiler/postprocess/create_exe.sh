#$1 is the name of the intput file (assembler file)
#s2 is the name of the output file (executable)

#!/bin/sh
#For 64-bit binary code, remove "--32"
as $1 -o $1".o" --32
#For 64-bit executable remove "-m elf_i386"
ld -s $1".o" -o $2 -m elf_i386
rm $1".o" 2>/dev/null
