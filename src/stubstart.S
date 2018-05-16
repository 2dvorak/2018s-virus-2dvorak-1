.intel_syntax noprefix

.globl _start
_start:
	nop
	nop
	nop
	nop
	xor rsp, rbp
	xor rsp, rbp
	nop
	nop
	nop
	nop
    call main
    #;jmp -0x0000
    mov rax, 60
    xor rdi, rdi
    syscall
    ret
