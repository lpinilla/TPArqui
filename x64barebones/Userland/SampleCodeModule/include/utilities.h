#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <stdio.h>
#include <syscall.h>

void print_f(char * format, ...);
void put_char(char c);
char get_char();
void clear_console(void);
void bash();

#endif
