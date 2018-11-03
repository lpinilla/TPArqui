#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdint.h>
#include <call_int_80.h>

#define READ 3
#define WRITE 4
#define DRAW_PIXEL 5
#define X_RES 6
#define Y_RES 7
#define CLEAR_SCREEN 8
#define SHADOW_PIXEL 9
#define MOVE_EVERYTHING_UP 10
#define SWAP_BUFFERS 11
#define CLEAR_SHADOW_BUFFER 12
#define TIME 13

void sys_write(char * string, int size);
char sys_read(char * string, int size);
void sys_clear_console();

#endif
