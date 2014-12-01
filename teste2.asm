global _start
section .data
test_marks dd 90,50,70,94, 81,40,67,55,60,73
NO_STUDENTS EQU ($-test_marks)/4
sum_msg db 'A soma eh: ',0
SIZE_MAG EQU $-sum_msg

section .bss
sum resd 1
sum_out resb 10
size_sum_out resb 1
section .text
_start:
	mov ecx, NO_STUDENTS
	sub eax, eax
	sub esi, esi

add_loop:
	add eax, [test_marks + esi*4]
	jmp PRINT
	volta1:
	inc esi
	loop add_loop
	mov [sum], eax





	mov eax, 1
	mov ebx, 0
	int 80h

PRINT:

push eax
push ebx
push ecx
push edx

mov eax, 4
mov ebx, 1

mov dword [test_marks] , 4
mov ecx, [test_marks]
mov edx, 4
int 80h


pop edx
pop ecx
pop ebx
pop eax

jmp volta1
