//inicio .h
#include <string.h>

#define BUFFER_SIZE 80

char buffer[BUFFER_SIZE];

char read_keyboard();
void erase_buffer();
void read_from_buffer(char * placeholder, int count);
char get_char();
int buffer_index = 0; //variable global

#define KEYBOARD_STATUS_PORT    0x64
#define KEYBOARD_DATA_PORT      0x60
#define BACKSPACE               128
#define ENTER_KEY               129
#define LEFT_SHIFT              130
#define RIGHT_SHIFT             131
#define CAPS_LOCK               132
#define UP_ARROW                133
#define DOWN_ARROW              134
#define LEFT_ARROW              135
#define RIGHT_ARROW             136
#define TRUE                    1
#define FALSE                   0
#define MAXCODE                 128
#define IS_LOWERCASE ((caps_lock && (left_shift || right_shift)) || (!caps_lock && !left_shift && !right_shift))
#define SHIFT_PRESSED (left_shift || right_shift)
#define IS_ARROW(k) (k == UP_ARROW || k == DOWN_ARROW || k == RIGHT_ARROW || k == LEFT_ARROW)
#define MAX_BUFF_SIZE           512
#define EOF -1

//mapa de caracteres
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
//fin .h
#include <naiveConsole.h> //para testear

void keyboard_handler(){
	char key = read_keyboard();
	ncPrintChar(keycode_map[key]);
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