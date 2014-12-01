define VAR 3
define VARIAVEL 2
section .bss
Z resw 0
X resw 2
section .text
global _start
_start:
add ax , [VARIAVEL]
imul word [VAøIAVEL]
mov eax, 1
mov ebx, 0,
int 80h
