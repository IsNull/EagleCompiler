global _start

section .text
_start:
mov edx,6
mov ecx,myText
mov ebx,1
mov eax,4
int 0x80

;systemcall exit(0)
push dword 0
mov eax,1
int 0x80

section .data
myText: db "foo", 0xa

