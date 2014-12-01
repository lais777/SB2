define VARIAVEL 2
section .bss
section .text
global _start
_start:
add ax , [VARIAVEL]
mov eax, 1
mov ebx, 0,
int 80h
