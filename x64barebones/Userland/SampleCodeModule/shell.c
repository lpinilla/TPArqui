#include <string.h>
#include <syscall.h>
#include <time.h>
#include <syscall.h>
#include <shell.h>
#include <pong.h>
#include <openlg.h>


static func execute_command[]={invalid_command,play_pong,show_time,shutdown,make_beep,make_div,ayuda};
const char * commands[] = {"pong", "time","shutdown","beep","div","ayuda"};


uint64_t * shell(void){
	draw_welcome_screen();
	print_f("Escriba ayuda para ver los comandos disponibles \n");
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
		else if (c!='\b' && (is_alpha(c) || is_digit(c) || is_symbol(c) || is_space(c))){ // este caso es el generico, sacamos el caso si es un backspace porque no hacemos nada
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
	init_game();
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
int is_space(unsigned char c){
	return (c==' ');
}
void make_beep(){
	sys_beep();
}

void make_div(){
	int n = 1;
	int b = 0;
	int c = n/b;
}

void ayuda(){
	print_f("\nBienvenido a nuestra shell \n");
	print_f("\nLos comandos disponibles son los siguientes \n \n \n");
	print_f("beep - Usa el pcspeaker para hacer sonido \n");
	print_f("pong - Ejecuta el juego pong \n");
	print_f("div - Levanta una excepcion de division por 0 \n");
	print_f("time - Devuelve la hora en formato GMT \n");
	print_f("shutdown - Apaga el SO \n \n \n");
	return;
}
