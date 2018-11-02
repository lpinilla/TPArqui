#include <keyboard.h>
#include <stdint.h>
#include <stdarg.h>

static void read(uint64_t param1, uint64_t param2, uint64_t param3);
static void write(uint64_t param1, uint64_t param2, uint64_t param3);

typedef void (*func)(uint64_t, uint64_t, uint64_t);
func syscall_pointers[] = {read, write};

void syscall_dispacher(uint64_t number, uint64_t param1, uint64_t param2, uint64_t param3) {
	syscall_pointers[number](param1,param2,param3);
	return;
}

void read(uint64_t param1, uint64_t param2, uint64_t param3) {
  /*cosas de read*/
}

void write(uint64_t param1, uint64_t param2, uint64_t param3) {
	/* cosas de write*/
}
