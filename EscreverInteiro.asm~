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
