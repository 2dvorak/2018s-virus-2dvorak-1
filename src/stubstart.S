.intel_syntax noprefix

.globl _start
_start:
    call main
    jmp -0x0000
    ;mov eax, 1
    ;xor ebx, ebx
    ;int 0x80
