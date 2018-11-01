#include <time.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	/*ncNewline();
	ncPrint("Timer-Tick Working");*/
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void time_wait(int n_ticks){
	int goal_ticks = ticks + n_ticks;
	while(ticks < goal_ticks);
}
