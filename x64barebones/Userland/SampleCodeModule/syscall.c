#include <syscall.h>

void sys_write(char * string, int size){
  _call_int_80((uint64_t) WRITE, 1, (uint64_t) string, size, 0, 0);
}
char sys_read(char * string, int size){
  return _call_int_80(READ, 1, (uint64_t) ((char *) string), size, 0, 0);
}

void sys_clear_console(){
	_call_int_80(CLEAR_SCREEN, 0,0,0,0,0);
}

void sys_draw_pixel(int x, int y, int r, int g, int b){
	_call_int_80(DRAW_PIXEL, x, y, r, g, b);
}

void sys_shadow_pixel(int x, int y, int r, int g, int b){
	_call_int_80(SHADOW_PIXEL, x, y, r, g, b);
}

void sys_swap_buffers(){
	_call_int_80(SWAP_BUFFERS, 0, 0, 0, 0, 0);
}

void sys_clear_shadow_buffer(){
	_call_int_80(CLEAR_SHADOW_BUFFER, 0, 0, 0, 0, 0);
}

void sys_color_write(char * string, int size, int foreground_color, int background_color){
	_call_int_80(COLOR_WRITE, string, size, foreground_color, background_color, 0);
}

void sys_reset_cursor(){
	_call_int_80(RESET_CURSOR, 0, 0, 0, 0, 0);
}