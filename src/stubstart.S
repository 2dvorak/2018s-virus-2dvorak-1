.intel_syntax noprefix

.globl _start
_start:
    call main
    mov eax, 1
    xor ebx, ebx
    int 0x80
