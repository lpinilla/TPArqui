#include <keyboard.h>
#include <naiveConsole.h> //para testear

//preguntar como se maneja esto

#define KEYBOARD_PORT 0x60

void keyboard_handler(){
	char key = io_write(KEYBOARD_PORT);
	ncPrintChar(keycode_map[key]); //para testear
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

char get_char(){
	unsigned char c = buffer[buffer_index++];
	if(buffer_index >= BUFFER_SIZE){
		buffer_index = 0;
	}
	return keycode_map[c];
}
