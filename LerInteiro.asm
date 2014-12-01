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
