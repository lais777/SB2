section .bss
x resb 13
section .data
teste db 'Hello', 0
section .text
global _start
_start:
mov eax, 4
mov ebx, 1
mov ecx, teste
mov edx, 5
int 80h

mov eax, 4
mov ebx, 1
mov ecx, teste
mov edx, 13
int 80h


call LeerChar

mov eax, 1
mov ebx,0
mov ecx, eax
int 80h


LeerChar:




enter 0,0 
push eax
push ebx
push ecx
push edx
push word [x]

loop:



mov eax, 3
mov ebx, 0
mov ecx, x
mov edx, 1

int 80h

mov eax, 4
mov ebx, 1
mov ecx, x
mov edx, 1
int 80h




cmp word[x], 0x0A
je FIM 

inc WORD [x]
jmp loop

FIM:
pop word [x]
leave 
ret 

