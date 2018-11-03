
#include <syscall.h>

void sys_write(char * string, int size){
  _call_int_80(WRITE,1,string,size,0,0);
}
char sys_read(char * string, int size){
<<<<<<< HEAD
  return _call_int_80(READ,1,string,size,0,0);
=======
  return syscall(READ,string,size,0,0,0);
>>>>>>> 138626a2f38ecc5379e0281bbdc1c8f04ed6e8cd
}
