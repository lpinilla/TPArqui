#include <keyboard.h>
#include <naiveConsole.h> //para testear
//preguntar como se maneja esto

uint8_t io_read(uint16_t port);

static char buffer[BUFFER_SIZE];
static int buffer_index; //variable global
static int caps_lock_pressed = FALSE;
static int l_shift_pressed= FALSE;
static int r_shitf_pressed= FALSE;

int is_alpha(unsigned char c);

#define CHECKBYTE(binary, index) (binary & 1<<(index)) // macro que checkea si el byte en la posicion index esta prendido

void keyboard_handler(){
	char key;
	if(CHECKBYTE(io_read(KEYBOARD_STATUS_PORT),0)) // verificamos que se pueda leer del port
		key = io_read(KEYBOARD_DATA_PORT);
	else
		return;
	if(key<0){ // nos fijamos si es una tecla soltada y por ahora solo tenemos en cuenta que los caracteres combinacion son los shift
		if(keycode_map[key+BREAK_CODE_DIF] == LEFT_SHIFT)
			l_shift_pressed=FALSE;
		if(keycode_map[key+BREAK_CODE_DIF] == RIGHT_SHIFT)
			r_shitf_pressed=FALSE;
		return;
	}
	if(keycode_map[key]==CAPS_LOCK){
		caps_lock_pressed=(caps_lock_pressed?FALSE:TRUE);
		return;
	}
	char c=keycode_map[key];
	if(caps_lock_pressed==TRUE){
		if(is_alpha(c))
				c-=32;
	}
	ncPrintChar(c); //para testear
	buffer[buffer_index++] = c;
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
int is_alpha(unsigned char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
