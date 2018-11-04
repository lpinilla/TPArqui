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
<<<<<<< HEAD
	for(int i = 0; i< 100000000; i++)
	_call_int_80(4,1,"Holas",3,0,0);

	return 0;
=======
	put_char('a');
	put_char('b');
	clear_console();
	put_char('c');
	return (uint64_t) (shell());
>>>>>>> dc3656691d0db7838e4c718dc4ee23c5ded6c3c6

}
