#include <time.h>
#include <stdint.h>

#include <naiveConsole.h>

static void int_20();
static void int_21();

typedef void (*func)();
func f_pointers[] = {int_20, int_21};

void irq_dispatcher(uint64_t irq) {
	f_pointers[irq]();
	return;
}

void int_20() {
	timer_handler();
}

void int_21() {
	//keyboard_handler();
	ncPrint("Teclado!");
}