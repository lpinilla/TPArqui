
#include <syscall.h>

void sys_write(char * string, int size){
  syscall(WRITE,string,size,0,0,0);
}
