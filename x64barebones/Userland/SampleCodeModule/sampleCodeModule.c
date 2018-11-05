#include <utilities.h>

uint64_t main() {
	/*
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	*/
	put_char('s');
	return (uint64_t) (shell());
	/*while (1) {
		put_char('v');
		put_char('a');
		put_char('m');
		put_char('o');
	}*/
	// (uint64_t) (shell());
	
	return (uint64_t) (shell());
}
