/* sampleCodeModule.c */
/*
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

*/

#include <utilities.h>

int main() {
	/*
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	*/
	char c='a';
	char b='b';
	put_char(c);
	put_char(b);
<<<<<<< HEAD
	clear_console();
	put_char('c');
	//while(1){};
=======
>>>>>>> refs/remotes/origin/master
	return 0xDEADBEEF;
}
