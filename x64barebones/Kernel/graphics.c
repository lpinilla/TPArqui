#include <stdio.h>
#include <graphics.h>


void draw_pixel(int x,int y, int r, int g, int b) {

	mode_info_block* infoBlock = (mode_info_block *) get_info_block();
	screen = infoBlock->physbase + x*infoBlock->bpp / 8 + y*infoBlock->pitch; //magic_number 8
    screen[0] = b;              // BLUE
    screen[1] = g;              // GREEN
    screen[2] = r;              // RED
}

//se podría usar con double buffering
void draw_fill_rect(unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    mode_info_block* infoBlock = (mode_info_block *) get_info_block();
    unsigned char *where = infoBlock->physbase;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            draw_pixel(j,i, r,g,b);       //ineficiente pintar de a 1 pixel a la vez, ver si podemos mejorar
        }
        where+=3200;
    }
}

/*
uint32_t font_data_lookup_table[16] = {
    0x00000000,
    0x000000FF,
    0x0000FF00,
    0x0000FFFF,
    0x00FF0000,
    0x00FF00FF,
    0x00FFFF00,
    0x00FFFFFF,
    0xFF000000,
    0xFF0000FF,
    0xFF00FF00,
    0xFF00FFFF,
    0xFFFF0000,
    0xFFFF00FF,
    0xFFFFFF00,
    0xFFFFFFFF
}
 
void draw_char(uint32_t character, uint8_t foreground_colour, uint8_t background_colour) {
    where = screen;
    int row;
    uint8_t row_data;
    uint32_t mask1, mask2;
    uint8_t *font_data_for_char = &system_font_data_address[character * 8];
    uint32_t packed_foreground = (foreground << 24) | (foreground << 16) | (foreground << 8) | foreground;
    uint32_t packed_background = (background << 24) | (background << 16) | (background << 8) | background;
 
    for (row = 0; row < 8; row++) {
        row_data = font_data_for_char[row];
        mask1 = font_data_lookup_table[row_data / 16];
        mask2 = font_data_lookup_table[row_data & 0x0F];
        *(uint32_t *)where = (packed_foreground & mask1) | (packed_background & ~mask1);
        *(uint32_t *)(&where[4]) = (packed_foreground & mask2) | (packed_background & ~mask2);
        where += bytes_per_line;
    }
}*/