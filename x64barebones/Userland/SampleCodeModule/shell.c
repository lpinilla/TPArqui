#include <utilities.h>

#define RETURN_ADRESS 0xDEADC0DE

uint64_t * shell();

uint64_t * shell(void){
	while(1){
		put_char('s');
	}
	return (uint64_t *) RETURN_ADRESS;
}
