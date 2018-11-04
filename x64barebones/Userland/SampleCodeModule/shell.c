#include <utilities.h>

uint64_t * shell();

uint64_t * shell(void){
	put_char('h');
	int i = 1;
	while(i){
		put_char('y');
	}
	return (uint64_t *) 0xDEADC0DE;
}