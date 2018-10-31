#define BUFFER_SIZE 80

char buffer[BUFFER_SIZE];

int read_keyboard();

//mapa de caracteres
#include <naiveConsole.h>

void keyboard_handler(){
	int key = read_keyboard();
	ncNewline();
	ncPrintChar(key);
	if(key == -1){ //algo malo

	}

}