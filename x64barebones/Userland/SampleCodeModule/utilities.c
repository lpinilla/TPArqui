
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


void print_number(int number){
  if (number == 0){
   put_char('0');
   return;
  }
  int n = get_digits(number);
  char array[n];
  for(int i = 0; i < n; i++){
    array[n-1-i] = number % 10;
    number /= 10;
  }
  for(int i = 0; i < n; i++){
    put_char(array[i] + '0');
  }
}

int get_digits(int number){
  if(number/10 == 0)
    return 1;
  return 1 + get_digits(number/10);
}


void clear_console(){
  sys_clear_console();
}
