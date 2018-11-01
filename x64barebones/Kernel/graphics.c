#include <stdio.h>
#include <graphics.h>
#include <bitmap.h>


void draw_pixel(int x,int y, int r, int g, int b) {

	mode_info_block* infoBlock = (mode_info_block *) get_info_block();
	screen = (char *) ((uint64_t) infoBlock->physbase + x*infoBlock->bpp / 8 + (int) y*infoBlock->pitch); //magic_number 8
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


unsigned char glyphs[] = {
  ________,
  ________,
  ___XX___,
  __XXXX__,
  __XXXX__,
  __XXXX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________,
  ________
};


//mascaras
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
};

char * letras[] = {
  "00000000",
  "00000000",
  "00011000",
  "00111100",
  "00111100",
  "00111100",
  "00011000",
  "00011000",
  "00011000",
  "00000000",
  "00011000",
  "00011000",
  "00000000",
  "00000000",
  "00000000",
  "00000000"
};

void draw_char(int x, int y){
  char c, index = 0;
  while(letras){
    c = letras[0][index++];
    if(c){
      draw_pixel(x,y,255,255,255);
    }
    x++;
  }
}

void draw_char2(int x, int y) {
    char * where;
    mode_info_block* infoBlock = (mode_info_block *) get_info_block();
    where = (char *) ((uint64_t) infoBlock->physbase + x*infoBlock->bpp / 8 + (int) y*infoBlock->pitch); //magic_number 8
    uint8_t row_data;
    uint32_t mask1, mask2;
    uint32_t foreground_colour = (WHITE.r << 16) + (WHITE.g << 8) + WHITE.b;

    uint8_t *font_data_for_char = glyphs;
    uint32_t packed_foreground = (foreground_colour << 24) | (foreground_colour << 16) | (foreground_colour << 8) | foreground_colour;
 
    for (int row = 0; row < 16; row++) {
        row_data = font_data_for_char[row];
        mask1 = font_data_lookup_table[row_data / 16];
        mask2 = font_data_lookup_table[row_data & 0x0F];
        *(uint32_t *)where = (packed_foreground & mask1);
        *(uint32_t *)(&where[4]) = (packed_foreground & mask2);
        //where += x + (y << 8) + (y << 6);
        where += infoBlock->pitch;
    }
}