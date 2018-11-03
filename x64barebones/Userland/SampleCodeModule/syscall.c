#include <syscall.h>

void sys_write(char * string, int size){
  _call_int_80(WRITE,1,string,size,0,0);
}
char sys_read(char * string, int size){
  return _call_int_80(READ,1,string,size,0,0);
}

void sys_clear_console(){
	_call_int_80(CLEAR_SCREEN, 0,0,0,0,0);
}

