
#include <utilities.h>

void print_string(char * s);

#define TRUE 1
#define FALSE 0

void put_char(char c){
  sys_write(&c,1);
}

void print_string(char *s){
  int i=0;
  while(s[i]!='\0'){
    sys_write(s+i,1);
    i++;
  }
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

void print_f(char * format, ...){
  if(format==NULL)
    return;
  int i=0;
  int flag=FALSE;
  char c;
  va_list va;
  va_start(va, format);
  while(format[i]!=0){
    switch(format[i]){
      case '%':
        if(flag){
          put_char('%');
          flag=FALSE;
        }
        else
          flag=TRUE;
        break;
      case 'd':
          if(flag){
            print_number(va_arg(va,int));
            flag=FALSE;
          }
          else
            put_char('d');
          break;
      case 's':
        if(flag){
          print_string(va_arg(va, char *));
          flag=FALSE;
        }
        else
          put_char('s');
        break;
      case 'c':
        if(flag){
          put_char(va_arg(va,int));
          flag=FALSE;
        }
        else
          put_char('c');
        break;

      default:
          put_char(format[i]);
    }
    i++;
  }
  va_end(va);
}


int get_digits(int number){
  if(number/10 == 0)
    return 1;
  return 1 + get_digits(number/10);
}


void clear_console(){
  sys_clear_console();
}
