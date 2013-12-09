.global _start

.text
_start:
movl foobar,%eax
addl answer,%eax
movl $6,%edx
movl $myText,%ecx
movl $1,%ebx
movl $4,%eax
int $0x80

//systemcall exit(0)
movl $0, %eax
movl $1,%eax
int $0x80

.data
answer: .word 42
foobar: .word 0
myText: .ascii "foo\n"

