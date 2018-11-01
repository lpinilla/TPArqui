#include <keyboard.h>
#include <naiveConsole.h> //para testear

//preguntar como se maneja esto

#define KEYBOARD_PORT 0x60
#define BUFFER_SIZE 80

int buffer_index = 0; //variable global
static char buffer[BUFFER_SIZE];

unsigned char keycode_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* INDEX: 0 - 9 */
    '9','0', '-', '=', BACKSPACE, '\t' /* Tab */,'q', 'w', 'e', 'r',	/* INDEX: 10 - 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER_KEY, 0 /* Control */, /* INDEX: 20 - 29 */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* INDEX: 30 - 39 */
 '\'', '`',  LEFT_SHIFT,'\\', 'z', 'x', 'c', 'v', 'b', 'n', /* INDEX: 40 - 49 */
  'm', ',', '.', '/', RIGHT_SHIFT,'*',0/* Alt */,' '/* Space bar */, CAPS_LOCK, 0 /* F1 */, /* INDEX: 50 - 59 */
    0/* F2 */,   0/* F3 */,   0/* F4 */,   0/* F5 */,   0/* F6 */,   0/* F7 */,   0/* F8 */,   0/* F9 */, 0 /*F10 */, 0/*Num lock*/, /* INDEX: 60 - 69 */
    0 /* Scroll Lock */,0 /* Home key */, UP_ARROW /* Up Arrow */, 0 /* Page Up */, '-', LEFT_ARROW/* Left Arrow */, 0, RIGHT_ARROW/* Right Arrow */,'+', 0/*End key*/, /* INDEX: 70 - 79 */
    DOWN_ARROW/* Down Arrow */,0/* Page Down */, 0/* Insert Key */, 0/* Delete Key */, 0,   0,   0,  0/* F11 Key */, 0/* F12 Key */,
    0,	/* All other keys are undefined */
};

char io_read(int a);


void keyboard_handler(){
	char key = io_read(KEYBOARD_PORT);
	ncPrintChar((unsigned char) keycode_map[key]); //para testear
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
