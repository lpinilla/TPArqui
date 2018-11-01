#include <stdio.h>

#include <naiveConsole.h>

#define PIXEL_SIZE 100
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

void draw_point(int x,int y, int r, int g, int b);
void load_vga_info();
void draw_pixel(unsigned char r, unsigned char g, unsigned   char b);

char * screen;


void draw_point(int x,int y, int r, int g, int b) {

	mode_info_block* infoBlock = (mode_info_block *) get_info_block();
	screen = infoBlock->physbase + x*infoBlock->bpp / 8 + y*infoBlock->pitch; //magic_number 8
    screen[0] = b;              // BLUE
    screen[1] = g;              // GREEN
    screen[2] = r;              // RED
}

//se podría usar con double buffering
void draw_pixel(unsigned char r, unsigned char g, unsigned   char b) {
    mode_info_block* infoBlock = (mode_info_block *) get_info_block();
    unsigned char *where = infoBlock->physbase;
    for (int i = 0; i < PIXEL_SIZE; i++) {
        for (int j = 0; j < PIXEL_SIZE; j++) {
            draw_point(j,i, r,g,b);
        }
        where+=3200;
    }
}