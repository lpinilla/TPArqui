#ifndef _SHELL_H_
#define _SHELL_H_

/*
PARA AGREGAR UN COMANDO HAY QUE AGREGARLO EN EL DEFINE EN ORDEN, DESPUES EN EL VECTOR DE FUNCIONES EN EL MISMO NUMERO DEL
DEFINE Y DESPUES EN EL VECTOR DE STRINGS ENE EL NUMERO DEL DEFINE -1 (podriamos cambiar esto para que sea mas consistente)
*/
#include <utilities.h>

#define EOF -1

#define RETURN_ADRESS 0xDEADC0DE

#define INVALID_COMMAND 0
#define PONG_COMMAND 1
#define TIME_COMMAND 2
#define SHUTDOWN_COMMAND 3
#define BEEP_COMMAND 4
#define MAKE_DIV 5
#define AYUDA 6


#define COMMANDS 6

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
void make_div();
void ayuda();
uint64_t * shell();


#endif