global read_keyboard

read_keyboard:
	push rbp
	mov rbp, rsp 		;pushear todo en realidad

	mov rax, 0
	in al, 60h
	push rax

	mov al, 20h
	out 20h, al
	pop rax

	leave
	ret