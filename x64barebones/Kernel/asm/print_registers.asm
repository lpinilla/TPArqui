GLOBAL print_all_registers

extern draw_string

section .text

print_all_registers:
    mov rdi, stringgg
    call draw_string
    ret

section .rodata
  stringgg db "RIP EXCEPCION"
