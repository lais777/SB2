global _start
section .bss
x resd 1
io_buf resb 12
char resd 1
section .text
_start:


mov eax, 100
push char

call _LerInteiro

;sub dword [char], 30h

push dword [char]
push dword [char]
push dword [char]
push dword [char]

call _EscreverInteiro
call _EscreverInteiro
call _EscreverInteiro
call _EscreverInteiro

mov eax, 1
mov ebx, 0
int 80h






_LerInteiro: 
	enter 0,0 
	push eax
	mov eax,3
	mov ebx,0
	mov ecx,io_buf
	mov edx,12
	int 80h
	mov eax,io_buf
	mov ebx,0
	mov ecx,0
_LIloop:
	mov bl,[eax]
	cmp bl,0Ah
	je _LIend
	cmp bl,0
	je _LIend
	sub bl,30h
	imul ecx,ecx,10
	add ecx,ebx
	inc eax
	jmp _LIloop
_LIend:
	mov edx,[EBP+8]
	mov [edx],ecx
	pop eax
	leave 
	ret 4
	
	
_EscreverInteiro:
	enter 0,0
	push eax
	mov esi,io_buf
	mov ebx,[EBP+8]
	mov ecx,10
	mov DWORD [esi],0
	mov DWORD [esi],0
	mov DWORD [esi],0
_EIloop:	
	mov edx,0
	mov eax,ebx
	idiv ecx
	add edx,30h
	mov BYTE [esi],dl
	mov ebx,eax
	inc esi
	cmp ebx,0
	jne _EIloop 
	mov eax,io_buf
	mov edx,esi
	dec esi
_EIswap:
	mov bl,[eax]
	mov cl,[esi]
	mov [eax],cl
	mov [esi],bl
	inc eax
	dec esi
	cmp eax,esi
	jl _EIswap
	mov BYTE [edx],0Ah 
	inc edx
	mov BYTE [edx],0
	mov eax,4
	mov ebx,1
	mov ecx,io_buf
	mov edx,12
	int 80h
	pop eax
	leave
	ret 4
