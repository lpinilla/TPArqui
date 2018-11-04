/* sampleCodeModule.c */
/*
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;
*/

#include <syscall.h>
#include <call_int_80.h>

uint64_t main() {
	/*
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	*/
	while (1) {
		put_char('v');
		put_char('a');
		put_char('m');
		put_char('o');
	}
	return;
	// (uint64_t) (shell());

}
