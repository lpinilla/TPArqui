GLOBAL _call_int_80

section .text

_call_int_80:
	push rbp
	mov rbp, rsp

  	int 80h

  	leave
  	ret
