#include <stdio.h>
#include <graphics.h>
#include <bitmap.h>
#include <glyphs.h>


void init_graphics(){
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
  //podría mostrar mensaje de bienvenida
}


void draw_pixel(int x, int y, int r, int g, int b) {
	screen = (char *) ((uint64_t) infoBlock->physbase + x*infoBlock->bpp / 8 + (int) y*infoBlock->pitch); //magic_number 8
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

//se podría usar con double buffering
void draw_fill_rect(unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    unsigned char *where = infoBlock->physbase;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            draw_pixel(j,i, r,g,b);
        }
        where+=3200;
    }
}

void draw_char_w_color(int x, int y, int c, int r, int g, int b){
  for(int i = 0; i < CHAR_HEIGHT; i++){
    for(int j = 0; j < CHAR_WIDTH; j++){
      if(*(&glyphs[(c-31) * CHAR_HEIGHT] + i * sizeof(uint8_t)) & 1<<j){
        draw_pixel(CHAR_WIDTH -1 -j + x, i +y,r,g,b);
      }
    }
  }
}


//draw in black background and white letters
void draw_char(char c){
  for(int i = 0; i < CHAR_HEIGHT; i++){
    for(int j = 0; j < CHAR_WIDTH; j++){
      if(*(&glyphs[(c-31) * CHAR_HEIGHT] + i * sizeof(uint8_t)) & 1<<j){
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,0xFF,0xFF,0xFF); //siempre en blanco con fondo negro
      }
    }
  }  
  x_cursor += CHAR_WIDTH;
}



void draw_string(char * string){
  int i = 0;
  while(*(string + i)){
    draw_char(string[i++]);
  }
}






/*
**Forma más eficiente de pintar chars, por cada fila del mapa de glyphs, 
**se encarga de copiar "toda la fila entera" en vez de hacer putpixel
**de cada caracter. 


void draw_char2(int x, int y) {
    char * where;
    mode_info_block* infoBlock = (mode_info_block *) get_info_block();
    where = (char *) ((uint64_t) infoBlock->physbase + x*infoBlock->bpp / 8 + (int) y*infoBlock->pitch); //magic_number 8
    uint8_t row_data;
    uint32_t mask1, mask2;
    uint8_t foreground_colour = (WHITE.r << 16) + (WHITE.g << 8) + WHITE.b;

    uint8_t *font_data_for_char = &glyphs[0];
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
}*/