#include <time.h>
#include <stdint.h>

static void int_20();

void irq_dispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			int_20();
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}