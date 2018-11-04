#include <utilities.h>

#define EOF -1

#define RETURN_ADRESS 0xDEADC0DE

uint64_t * shell();

uint64_t * shell(void){
	char c;
	while(1){
		if((c=get_char())!=EOF)
				put_char(c);
	}
	return (uint64_t *) RETURN_ADRESS;
}
