global      _start                              ;must be declared for linker (ld)

;Some constants
sys_exit equ 1
sys_read equ 3
sys_write equ 4
stdin equ 0
stdout equ 1
stderr equ 2
LF equ 10

section     .text

_start:                                         ;tell linker entry point

    mov     edx,0xFF                             ;message length
    mov     ecx,msg                             ;message to write
    mov     ebx,stdout                          ;file descriptor (stdout)
    mov     eax,sys_write                       ;system call number (sys_write)
    int     0x80                                ;call kernel

    mov     eax,sys_exit                        ;system call number (sys_exit)
    int     0x80                                ;call kernel
;------------------------------------------------------------------------------
GetStrlen:
	push    ebx
	xor     ecx, ecx
	not     ecx
	xor     eax, eax
	cld
	repne   scasb
	mov     byte [edi - 1], 10
	not     ecx
	pop     ebx
	lea     edx, [ecx - 1]
ret


section     .data
msg     db  'Hello, world!',0xa                 ;our dear string
times 0x256-($-msg) db 0
