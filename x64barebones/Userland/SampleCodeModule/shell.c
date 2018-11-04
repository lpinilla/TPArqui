#include <utilities.h>

uint64_t * shell();

uint64_t * shell(void){
	put_char('h');
	put_char('o');
	put_char('l');
	put_char('a');	

	/*while(1){
		put_char('g');
	}*/
	return (uint64_t *) 0xDEADC0DE;
}
