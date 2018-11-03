
#include <utilities.h>


void put_char(char c){
  sys_write(&c,1);
}

void print_f(char * format, ...){
  if(format==NULL)
    return;
}
char get_char(){
  char c;
  return sys_read(&c,1);
}

void bash(){
  while(1);
}
