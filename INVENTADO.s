%define VAR 3
%define VARIAVEL 2
section .bss
io_buf resb 12
Z resw 0
X resw 2
section .text
global _start
_start:
add ax , [VARIAVEL]
imul word [VAR]
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
c8 00 00 00 50 b8 03 00 00 00 bb 00 00 00 00 b9 88 91 04 08n ba 0c 00 00 00 cd 80 bb 00 00 00 00 b9 00 00 00 00 8a 18 80 fb 0a 74 10 80 fb 00 74 0b 80 eb 30 6b c9 0a 01 d9 40 eb e9 8b 55 08 89 0a 58 c9 c2 04 00 _EscreveInteiro:
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
mov bl,[eax]
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
c8 00 00 00 
50
be 88 91 04 08
8b 5d 08
b9 0a 00 00 00
c7 06 00 00 00 00
c7 06 00 00 00 00 
c7 06 00 00 00 00
ba 00 00 00 00
89 d8
f7 f9
83 c2 30
88 16
89 c3 
46
83 fb 00
75 ea
b8 88 91 04 08
89 f2
4e
8a 18
8a 0e
88 08
88 1e
40
4e
39 f0
7c f2
c6 02 0a
42 
c6 02 00 
b8 04 00 00 00
bb 01 00 00 00 
b9 88 91 04 08
ba 0c 00 00 00
cd 80
58
c9 
c2 04 00
