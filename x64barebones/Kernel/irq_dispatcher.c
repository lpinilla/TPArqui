#include <time.h>
#include <stdint.h>

static void int_20();

typedef void (*func)();
func f_pointers[] = {int_20};

void irq_dispatcher(uint64_t irq) {
	f_pointers[irq]();
	return;
}

void int_20() {
	timer_handler();
}