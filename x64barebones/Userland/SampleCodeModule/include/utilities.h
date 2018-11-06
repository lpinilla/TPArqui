#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <stdarg.h>
#include <stdio.h>
#include <syscall.h>
#include <string.h>

void print_f(char * format, ...);
void put_char(char c);
char get_char();
void clear_console(void);
int get_digits(int number);
int get_number(char * buffer, int * pointer, int * index);
void print_number(number);
uint64_t * shell();

#endif
