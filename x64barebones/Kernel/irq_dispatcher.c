#include <stdint.h>
#include "irq_dispatcher.h"

void ncPrint();
void ncClear();

typedef void (* func)(void);
func f_pointers[] = {int_20, int_21};

void irq_dispatcher(uint64_t irq){
	f_pointers[irq]();
	return;
}

void int_20(){
	//time_handler();
}

//Teclado
void int_21(){
	//keyboard_handler();
	ncClear();
	ncPrint("yay");
}