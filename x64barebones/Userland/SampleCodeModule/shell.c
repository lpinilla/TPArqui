#include <utilities.h>
#include <string.h>
#include <syscall.h>
#include <time.h>
#include <syscall.h>
/*
PARA AGREGAR UN COMANDO HAY QUE AGREGARLO EN EL DEFINE EN ORDEN, DESPUES EN EL VECTOR DE FUNCIONES EN EL MISMO NUMERO DEL
DEFINE Y DESPUES EN EL VECTOR DE STRINGS ENE EL NUMERO DEL DEFINE -1 (podriamos cambiar esto para que sea mas consistente)
*/


#define EOF -1

#define RETURN_ADRESS 0xDEADC0DE

#define INVALID_COMMAND 0
#define PONG_COMMAND 1
#define TIME_COMMAND 2
#define SHUTDOWN_COMMAND 3
#define BEEP_COMMAND 4

#define COMMANDS 4

#define MAX_LENGTH 20

typedef void (*func)();

int is_digit(unsigned char c);
int is_alpha(unsigned char c);
int is_symbol(unsigned char c);
void invalid_command();
void play_pong();
void show_time();
void shutdown();
void print_user();
void make_beep();
static func execute_command[]={invalid_command,play_pong,show_time,shutdown,make_beep};
const char * commands[] = {"pong", "time","shutdown","beep"};

uint64_t * shell();

uint64_t * shell(void){
	print_user();
	int i=0;
	char command[MAX_LENGTH];
	char c;
	int command_id=INVALID_COMMAND;
	while(command_id!=SHUTDOWN_COMMAND){
		c=get_char();
		if(c=='\b' && i!=0){  // si es un backspace y no estamos al principio de linea, volvemos el indice hacia atras
			put_char(c);
			i--;
		}
		else if(c=='\n'){ // si es una new line entramos
			put_char(c); // imprimimos la new line
			if(i<MAX_LENGTH){  // si nuestro indice es menor al de comando maximo significa que puede ser un comando valido
				command[i]=0;  // le ponemos al final un 0 para saber donde termina
				command_id=command_handler(command); // lo mandamos al handler para que se encargue de decirnos que comando es
				execute_command[command_id](); // ejecutamos el comando
			}
			else // este es el caso que entramos a una new line y el comando es mas largo que MAX LENGHT
				invalid_command();  // mandamos un mensaje de comando invalido
			i=0; // reseteamos el contador a 0 ya que empezamos una nueva linea
			print_user();
		}
		else if (c!='\b' && (is_alpha(c) || is_digit(c) || is_symbol(c))){ // este caso es el generico, sacamos el caso si es un backspace porque no hacemos nada
			put_char(c);
			if(i<MAX_LENGTH) // si el indice todavia es menor que el maximo seguimos poniendolo en el comando
				command[i]=c;
			i++; //subimos el indice OJO QUE ES POSIBLE QUE HAYA OVERFLOW SI EL INDICE ES MUY GRANDE(SE ESCRIBE UN COMANDO ENORME MAS GRANDE QUE INT)
		}
	}
	return (uint64_t *) RETURN_ADRESS;
}
int command_handler(char * command){
	for(int i=0; i<COMMANDS; i++){
		if(str_cmp(command, commands[i])==0){
			return i+1;
		}
	}
	return INVALID_COMMAND;

}

void invalid_command(){
	print_f("Invalid command \n");
}

void shutdown(){
	print_f("Thank you, powering off \n");
}
void play_pong(){
	print_f("Aca jugamos al pong \n");
}
void show_time(){
	print_time();
}
void print_user(){
	print_f("ARQ@ITBA:");
}
int is_alpha(unsigned char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int is_digit(unsigned char c) {
    return (c >= '0' && c <= '9');
}
int is_symbol(unsigned char c){
	return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c>='[' && c <= '\'') || (c>='{' && c <='~'));
}
void make_beep(){
	sys_beep();
}
