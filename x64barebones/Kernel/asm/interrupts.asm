%macro pushState 0
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsi
	push rdi
	push rbp
	push rdx
	push rcx
	push rbx
	push rax
%endmacro

%macro popState 0
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rbp
	pop rdi
	pop rsi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
%endmacro

extern irq_dispatcher
global _irq00Handler
global _irq01Handler
global _cli
global _sti
global picMasterMask
global picSlaveMask


%macro irqHandlerMaster 1
	pushState
	mov rdi, %1
	call irq_dispatcher

						;signal to pic EOI (End of Interruption)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

_cli:
	cli
	ret

_sti:
	sti
	ret

picMasterMask:			;pic principal
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask: 			;pic secundario
	push    rbp
    mov     rbp, rsp
    mov     ax, di  	;ax = mascara de 8 bits
    out	0A1h,al
    pop     rbp
    retn

						
_irq00Handler:			;TimerTick
	irqHandlerMaster 0
						
_irq01Handler:			;KEYBOARD
	irqHandlerMaster 1