#include <stdio.h>

#include <naiveConsole.h>

//unsigned char *pixel = vram + y*pitch + x*pixelwidth;

/*
0x5080	+++ 32-bit VIDEO_BASE Base memory for video (if graphics mode set)
0x5084	+++ 16-bit VIDEO_X X resolution
0x5086	+++ 16-bit VIDEO_Y Y resolution
0x5088	+++ 8-bit VIDEO_DEPTH Color depth*/

static uint8_t * const video_dir = (uint8_t*)0xB8000;

unsigned char * pixel;
void print_pixel(void);

void print_pixel(){
	
}