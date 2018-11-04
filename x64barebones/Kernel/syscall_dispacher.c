#include <keyboard.h>
#include <stdint.h>
#include <stdarg.h>
#include <graphics.h>
#include <rtc.h>

#define READ 3
#define WRITE 4
#define DRAW_PIXEL 5
#define X_RES 6
#define Y_RES 7
#define CLEAR_SCREEN 8
#define SHADOW_PIXEL 9
#define MOVE_EVERYTHING_UP 10
#define SWAP_BUFFERS 11
#define CLEAR_SHADOW_BUFFER 12
#define TIME 13

int read(int param1, char * param2, int param3);
void write(int param1, char * param2, int param3);

// usamos la convencion de linux y c para los parametros de las syscalls
uint64_t syscall_dispacher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
  switch(rdi){
      case READ:
        read(rsi,(char *)rdx,rcx);
        break;
      case WRITE:
        write(rsi,(char *) rdx, rcx);
        break;
      case DRAW_PIXEL:
        draw_pixel(rsi,rdx,rcx,r8,r9);
        break;
      case X_RES:
        return get_x_res();
      case Y_RES:
        return get_y_res();
      case CLEAR_SCREEN:
        clear_screen();
        break;
      case TIME:
        return get_time(rsi);
      case SHADOW_PIXEL:
        shadow_pixel(rsi, rdx, rcx, r8, r9);
        break;
      case MOVE_EVERYTHING_UP:
        move_everything_up();
        break;
      case SWAP_BUFFERS:
        swap_buffers();
        break;
      case CLEAR_SHADOW_BUFFER:
        clear_shadow_buffer();
        break;
  }
	return 0;
}

int read(int fd, char * pointer, int size) {
  char c;
  for(int i=0; i<size; i++){
    c=get_char();
    if(c==EOF){
      return i;
    }
    pointer[i]=c;
  }
  return size;
}

void write(int fd, char * pointer, int size) {
  // por ahora solo implementamos por salida estandar (en nuestro caso pantalla), y el numero de salida estandar es 1
	if(fd!=1) 
    return;
  draw_n_chars(pointer,size);
}
