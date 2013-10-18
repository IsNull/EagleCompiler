.globl _start 

.text
_start:
xor %eax, %eax
movl $0,%ebx
movl $1,%eax
int $0x80

.data

