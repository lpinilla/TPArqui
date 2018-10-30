#include <stdint.h>
#include "idt_loader.h"


void setup_IDT_entry(int index, uint64_t offset){
	idt[index].offset_1 = offset & 0xFFFF;
	idt[index].selector = 0x08;
	idt[index].cero = 0x0;
	idt[index].access = ACS_INT;
	idt[index].offset_m = (offset >> 16) & 0xFFFF;
	idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
	idt[index].other_cero = 0x0;
}

void load_idt(){
	_cli();

	setup_IDT_entry(0x20, (uint64_t) &_irq00Handler);
	setup_IDT_entry(0x21, (uint64_t) &_irq01Handler);

	picMasterMask(0xFD); //solo habiitar el teclado
	picSlaveMask(0XFF);	 //deshabilitar todo del slave
	_sti();
}