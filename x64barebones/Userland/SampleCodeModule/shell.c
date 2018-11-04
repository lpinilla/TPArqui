#include <utilities.h>

uint64_t * shell();

uint64_t * shell(void){
	put_char('h');
	for(int i=0; i<10000; i++){
		put_char('h');
	}
	return (uint64_t *) 0xDEADC0DE;
}
