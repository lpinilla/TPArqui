#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <stdint.h>

#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

typedef struct __attribute__((packed)) {
  uint16_t attributes;
  uint8_t winA,winB;
  uint16_t granularity;
  uint16_t winsize;
  uint16_t segmentA, segmentB;
  uint32_t realFctPtr;
  uint16_t pitch; // bytes per scanline
 
  uint16_t Xres, Yres;
  uint8_t Wchar, Ychar, planes, bpp, banks;
  uint8_t memory_model, bank_size, image_pages;
  uint8_t reserved0;
 
  uint8_t red_mask, red_position;
  uint8_t green_mask, green_position;
  uint8_t blue_mask, blue_position;
  uint8_t rsv_mask, rsv_position;
  uint8_t directcolor_attributes;
 
  uint32_t physbase;  // your LFB (Linear Framebuffer) address ;)
  uint32_t reserved1;
  uint16_t reserved2;
} mode_info_block;

mode_info_block* get_info_block() {
	return (mode_info_block*)0x0000000000005C00;
}

void draw_pixel(int x,int y, int r, int g, int b);
void load_vga_info();
void draw_fill_rect(unsigned char r, unsigned char g, unsigned   char b, unsigned char size);

char * screen;

#endif