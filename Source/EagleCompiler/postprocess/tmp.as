

.global _start
.data

.text
_start:
movl $0, %eax
movl $1,%eax
int $0x80

