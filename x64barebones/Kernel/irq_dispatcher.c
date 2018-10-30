#include <stdint.h>

void int_20(void);
void int_60(void);
void time_handler(void);
void keyboard_handler(void);
void irqDispatcher(uint64_t irq);

typedef void (* func)(void);
func f_pointers[] = {int_20, int_60};

void irq_dispatcher(uint64_t irq){
	f_pointers[irq]();
	return;
}

void int_20(){
	//time_handler();
}

//Teclado
void int_60(){
	//keyboard_handler();
}