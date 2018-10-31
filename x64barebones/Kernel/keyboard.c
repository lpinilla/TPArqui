#include <string.h>

#define BUFFER_SIZE 80

char buffer[BUFFER_SIZE];

char read_keyboard();
void erase_buffer();
void read_from_buffer(char * placeholder, int count);
int buffer_index = 0; //variable global

//mapa de caracteres
#include <naiveConsole.h>

void keyboard_handler(){
	char key = read_keyboard();
	ncNewline();
	ncPrintChar(key);
	if(key == -1){ //no leyó?

	}
	buffer[buffer_index++] = key;
	if(buffer_index >= BUFFER_SIZE){
		buffer_index = 0;
	}
}

void erase_buffer(){ //set all buffer to 0
	memset(buffer, 0, BUFFER_SIZE * sizeof(char));
}

/*Salvo verificar si es null, no se verifica nada de placeholder
**Se lee siempre desde el principio y después se mueve el index*/
void read_from_buffer(char * placeholder, int count){ 
	if(count < 0 || placeholder == NULL){
		return;
	}
	//pasar al buffer
	memcpy(placeholder, buffer, count * sizeof(char)); 
	//pasar todas las demas al comienzo
	int desp = (BUFFER_SIZE - buffer_index) * sizeof(char);
	memcpy(buffer, buffer + buffer_index * sizeof(char), desp);
	//setear lo que quedó sin desplazar en 0
	memset(buffer + desp, 0, count);
}