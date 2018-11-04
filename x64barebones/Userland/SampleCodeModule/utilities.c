
#include <utilities.h>


void put_char(char c){
  sys_write(&c,1);
}

void print_f(char * format, ...){
  if(format==NULL)
    return;
  int i;
  while(format[i]!=0){
    put_char(format[i]);
    i++;
  }
  //parsing format
}
char get_char(){
  char c=EOF;
  while(c==EOF)
    sys_read(&c,1);
  return c;
}

void clear_console(){
  sys_clear_console();
}
