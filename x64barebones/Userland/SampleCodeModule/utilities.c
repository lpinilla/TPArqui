#include <utilities.h>

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

int print_f(const char * format, ...){
  if(format==NULL)
    return 0;
  int i=0;
  int flag=FALSE;
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
  return i;
}


int get_digits(int number){
  if(number/10 == 0)
    return 1;
  return 1 + get_digits(number/10);
}


void clear_console(){
  sys_clear_console();
}

int scan_f(const char* c, ...){
	va_list va;
	va_start(va,c);

	int ret = 0;
	int flag = 0;
	int i = 0;
	char buffer[MAX];
	int j = 0;
	char currentChar;

	while((currentChar = get_char()) != '\n'){
		if(currentChar == '\b'){
			if(j>0){
				buffer[--j] = 0;
				print_f("\b");
			}
		}else{
			if(j < MAX){
				buffer[j++]	= currentChar;
				put_char(currentChar);
			}
		}
	}
	buffer[j] = 0;
	j = 0;
	while(c[i]!=0&&ret>=0){
		switch(c[i]) {
			case '%':
				if(flag) {
					if(buffer[j]!='%')
						ret = -1;
					else
						j++;
				} else {
					flag = TRUE;
				}
				break;
			case 'd':
				if(flag){
					if(get_number(buffer, va_arg(va, int *), &j))
            ret++;
				  else
            ret = -1;
          flag = FALSE;
        }
        else{
					       if(buffer[j]!='d')
						           ret = -1;
					       else
						     j++;
				  }
				  break;
          case 's':
                if(flag){
                    j += str_cpy(buffer+j,va_arg(va,char*));
                    ret++;
                    flag = 0;
                  } else {
                    if(buffer[j]!='s')
                      ret = -1;
                    else
                      j++;
                  }
                  break;
        default:
            if(buffer[j]!=c[i])
              ret = -1;
            else
              j++;
		}
		i++;
	}
	va_end(va);
	return ret;
}
int get_number(char * array, int * pointer, int * index){
  *pointer = 0; // limpio el puntero
	int ret = 0; // auxiliar de retorno
	char c; // auxiliar de char
	int flag = TRUE;
	do{
		c = array[*index];  //asigno el auxiliar al indice del array
		if(is_digit(c)){  // si lo que asigne es un numero
			*pointer = (*pointer)*10; // multiplico al puntero por 10 para agregar un 0
			*pointer += c - '0';  // le sumo el ascii del numero
			ret = TRUE; //ponemos en true ya que pudimos leer al menos un numero
			*index = (*index)+1; //sumamos el indice
		}
    else {
			flag = FALSE;
		}
	} while(flag);
	return ret;
}

int is_alpha(unsigned char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int is_digit(unsigned char c) {
    return (c >= '0' && c <= '9');
}
int is_symbol(unsigned char c){
	return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c>='[' && c <= 96) || (c>='{' && c <='~'));
}
int is_space(unsigned char c){
	return (c==' ');
}
