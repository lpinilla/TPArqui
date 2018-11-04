
#include <utilities.h>


void put_char(char c){
  sys_write(&c,1);
}

void print_f(char * format, ...){
  if(format==NULL)
    return;
  //parsing format
}
char get_char(){
  char c;
  return sys_read(&c,1);
}

void bash(){
    char c;
  while(1){
    c=get_char();
    put_char(c);
  }
  return;
}

void clear_console(){
  sys_clear_console();
}