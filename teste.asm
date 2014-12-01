section .bss
x resw 3
cont resw 1

section .data
teste db 'Hello', 0
erro db 'ERRO',0


section .text
global _start
_start:
mov eax, 4
mov ebx, 1
mov ecx, teste
mov edx, 5
int 80h


call LeerChar

mov eax, 1
mov ebx,0
int 80h


LeerChar:




enter 0,0 
push eax
push ebx
push ecx
push edx
push word [x]

mov word [x], 0

mov word [cont], 1
loop:

mov eax, 3
mov ebx, 0
mov edx, [cont]
mov ecx, [x + edx ]
mov edx, 1

int 80h
inc word [cont]
;cmp word [cont], 3
;jg ERRO 

mov edx, [cont]
;cmp word [x+edx], 0x0A
;je FIM

mov eax, 4
mov ebx, 1
mov ecx, [cont]
mov edx, 1

int 80h




;mov ax, [cont]
;inc [x+ ax]
jmp loop

FIM:



mov eax, 4
mov ebx, 1
mov ecx, x
mov edx, [cont]
int 80h


continuacao:
pop word [x]
pop edx
pop ecx
pop ebx
pop eax
leave 
ret 


ERRO:
mov ecx, erro
mov eax, 4
mov ebx, 1
mov edx, 5
int 80h
jmp continuacao






