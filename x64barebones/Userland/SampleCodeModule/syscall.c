
#include <syscall.h>

void sys_write(char * string, int size){
  syscall(WRITE,string,size,0,0,0);
}
char sys_read(char * string, int size){
  return syscall(READ,string,size,0,0,0);
}
