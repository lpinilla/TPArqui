#include <keyboard.h>
#include <stdint.h>
#include <stdarg.h>
#include <graphics.h>

#define READ 3
#define WRITE 4
#define DRAW_PIXEL 5

void read(uint64_t param1, uint64_t param2, uint64_t param3);
void write(int param1, char * param2, int param3);

// usamos la convencion de linux y c para los parametros de las syscalls
void syscall_dispacher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
  switch(rdi){
      case READ:
        //read(va_arg(ap,int),va_arg(ap,int),va_arg(ap,int));
        break;
      case WRITE:
        write(rsi,(char *) rdx, rcx);
        break;
      case DRAW_PIXEL:
        draw_pixel(rsi,rdx,rcx,r8,r9);
        break;
  }
	return;
}

void read(uint64_t param1, uint64_t param2, uint64_t param3) {
  /*cosas de read*/
}

void write(int fd, char * pointer, int size) {
	if(fd!=1) // por ahora solo implementamos por salida estandar (en nuestro caso pantalla), y el numero de salida estandar es 1
    return;
  draw_n_chars(pointer,size);
}
