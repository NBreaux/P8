	.386
	.model	flat,stdcall
	.code
main	proc
	call	ini
v53,%eax
%eax,c50
v50,%eax
%eax,c51
v51,%eax
%eax,v53
%eax,c51
_0:
	pushl	%eax
%eax,v50
v52,%eax
%eax,v51
v50,%eax
%eax,v51
%eax,v52
v51,%eax
%eax,v51
	call	outi
	popl	%eax
	decl	%eax
	jle	_1
	jmp	_0
_1:
	xor	eax,eax
	ret
main	endp
	.data
c50	dd	-1
c51	dd	1
v50	dd	?	;a
v51	dd	?	;b
v52	dd	?	;c
v53	dd	?	;n
	extern	ini@0:near
	extern	outi@0:near
	end
