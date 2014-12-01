global _start
section .bss
x resw 1
y resw 1
z resw 1
sum_out resb 10
size_sum_out resb 1
section .text
_start:
add ax, [x]
add ax, [y]
add ax, [z]


mov eax, 1
mov ebx, 0
int 80h

x1:

x2:

x3: