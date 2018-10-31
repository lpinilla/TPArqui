#include <stdint.h>
#include <idt_loader.h>
#include <defs.h>
#include <interrupts.h>
#include <naiveConsole.h>

void load_idt() {

	//_cli();
	
	//exception
 	setup_IDT_entry (0x00, (uint64_t)&_exception0_handler);

 	//drivers
	setup_IDT_entry (0x20, (uint64_t)&_irq00_handler);
	setup_IDT_entry(0x21, (uint64_t)&_irq01_handler);


	pic_master_mask(0xFC);  //timer tick
	pic_slave_mask(0xFF); //todo des-habilitado
    
	_sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}