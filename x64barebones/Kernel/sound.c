#include <sound.h>

extern void io_write(uint16_t port, uint8_t data);
extern uint8_t io_read(uint16_t port);

#define PIT_3_PORT 0x42
#define PIT_CONFIGURE_PORT 0x43
#define NOT_KEYBOARD_PORT 0x61

void play_sound(int frequence_div) {
 int freq;
 uint8_t read_data;
 uint8_t aux;
 freq = 1193180 / frequence_div;
 io_write(PIT_CONFIGURE_PORT, 0xb6);
 io_write(PIT_3_PORT, (uint8_t) (freq) );
 io_write(PIT_3_PORT, (uint8_t) (freq >> 8));

 aux = io_read(NOT_KEYBOARD_PORT);
   if (aux != (aux | 3)) {
   io_write(NOT_KEYBOARD_PORT, aux | 3);
 }
}


void nosound() {
 uint8_t aux = io_read(NOT_KEYBOARD_PORT) & 0xFC;
 io_write(NOT_KEYBOARD_PORT, aux);
}

void beep() {
  play_sound(10000);
  time_wait(1);
  nosound();
}
