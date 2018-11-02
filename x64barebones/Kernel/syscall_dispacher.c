#include <keyboard.h>
#include <stdint.h>
#include <stdarg.h>
#include <graphics.h>

#define READ 1
#define WRITE 2
#define DRAW_PIXEL 3

void read(uint64_t param1, uint64_t param2, uint64_t param3);
void write(uint64_t param1, uint64_t param2, uint64_t param3);

void syscall_dispacher(uint64_t number, ...) {
  va_list ap;
  switch(number){
      case READ:
        va_start(ap, 3);
        read(va_arg(ap,int),va_arg(ap,int),va_arg(ap,int));
        break;
      case WRITE:
        va_start(ap,3);
        read(va_arg(ap,int),va_arg(ap,int), va_arg(ap,int));
        break;
      case DRAW_PIXEL:
        va_start(ap,5);
        draw_pixel(va_arg(ap,int),va_arg(ap,int), va_arg(ap,int),va_arg(ap,int),va_arg(ap,int));
        break;
      default:
        va_start(ap,1);
  }
  va_end(ap);
	return;
}

void read(uint64_t param1, uint64_t param2, uint64_t param3) {
  /*cosas de read*/
}

void write(uint64_t param1, uint64_t param2, uint64_t param3) {
	/* cosas de write*/
}
