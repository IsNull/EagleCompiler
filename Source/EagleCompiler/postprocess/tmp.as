global start

section .text
start:
push dword 4
push myText
push 1
mov eax, 0x4
sub esp, 4  
int 0x80

;systemcall exit(0)
push dword 0
mov eax, 0x1
sub esp, 4  
int 0x80
ret


section .data
myText: db "foo", 0xa

