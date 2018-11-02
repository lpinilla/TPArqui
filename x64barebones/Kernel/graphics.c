#include <stdio.h>
#include <stdint.h>
#include <graphics.h>
#include <bitmap.h>
#include <glyphs.h>

//resolucion 1024*768

//-----------------Variables locales
unsigned char * screen; //se usa para no estar creandolo todo el tiempo
int x_cursor, y_cursor;
mode_info_block* info_block;

char * title[9] = {"      ##      ##                           ",
                   "      ##      ##                TP DE ARQUI",
                   "    ##############                         ",
                   "  ####  ######  ####                       ",
                   "######################                     ",
                   "##  ##############  ##                     ",
                   "##  ##          ##  ##                     ",
                   "      ####  ####                           ",
                   "Pls profes aprueben el TP                  "};
//-----------------Fin variables locales

void init_graphics(){
  info_block = (mode_info_block*)0x0000000000005C00;
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
  for(int i = 0; i < 9; i++){
    draw_string(title[i]);
    new_line();
  }
  /*color WHITE = {.r = 0xFF, .g = 0xFF, .b = 0xFF};
  color BLACK = {.r = 0x0, .g = 0x0, .b = 0x0};*/
  /* memset(shadow_buffer, 0, info_block->x_res * info_block->y_res); */
  //podría mostrar mensaje de bienvenida
}


void draw_pixel(int x, int y, int r, int g, int b) {
	screen = (char *) ((uint64_t) info_block->physbase + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_char_w_color(int x, int y, char c, int r, int g, int b){
  if(x_cursor >= info_block->x_res){
    x_cursor = 0;
    if(y_cursor >= info_block->y_res - CHAR_HEIGHT){
      //mover todo para arriba
      move_everything_up();
    }else{
      y_cursor += CHAR_HEIGHT;
    }
  }
  for(int i = 0; i < CHAR_HEIGHT; i++){
    for(int j = 0; j < CHAR_WIDTH; j++){
      if(*(&glyphs[(c-31) * CHAR_HEIGHT] + i * sizeof(uint8_t)) & 1<<j){
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,r,g,b);
      }else{
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,0,0,0); //necesito esto para poder borrar
      }
    }
  }
  x_cursor += CHAR_WIDTH;
}


//draw in black background and white letters
void draw_char(char c){
  draw_char_w_color(x_cursor, y_cursor, c, 0XFF, 0XFF, 0XFF);
}


void draw_string(char * string){
  int i = 0;
  while(*(string + i)){
    draw_char(string[i++]);
  }
}
void draw_n_chars(char * s, int index){
  for(int i = 0 ; i< index; i++){
    draw_char(s[i]);
  }
}

//verificar los límites
void erase_character(){
  if(x_cursor == 0){
    if(y_cursor == 0){
      draw_char_w_color(x_cursor, y_cursor, ' ', 0xFF,0xFF,0xFF);
    }else{
      y_cursor -= CHAR_HEIGHT;
      x_cursor = info_block->x_res - CHAR_WIDTH;
      draw_char_w_color(x_cursor, y_cursor, ' ', 0xFF,0xFF,0xFF);
    }
  }else{
    x_cursor -= CHAR_WIDTH;
    draw_char_w_color(x_cursor, y_cursor, ' ', 0xFF,0xFF,0xFF);
  }
  x_cursor -= CHAR_WIDTH;
}

//testeable
int number_of_digits(int n){
  if(n == 0)  return 0;
  return 1 + number_of_digits(n/10);
}

//testeable
void draw_number(int n){
  if (n == 0){
   draw_char('0');
   return;
  }
  int count = number_of_digits(n);
  int array[count];
  for(int i = 0; i < count; i++){
    array[count-1-i] = n % 10;
    n /= 10;
  }
  for(int i = 0; i < count; i++){
    draw_char(array[i] + '0');
  }
}

void clear_screen(){
  memset(info_block->physbase, 0, info_block->y_res * info_block->x_res);
}

void new_line(){
  if(y_cursor != info_block->y_res){
    y_cursor += CHAR_HEIGHT;
  }
  x_cursor = 0;
}

//ver si podemos usar memcpy
void move_everything_up(){
  for(int i = 0; i < info_block->y_res; i++){
    for(int j = 0; j < info_block->x_res; j++){
      copy_pixel(i,j, i, j + CHAR_HEIGHT);
    }
  }
}


void copy_pixel(int x1,int y1,int x2,int y2){
  unsigned char* src = (char *) ((uint64_t)(info_block->physbase + info_block->pitch * y2 + x2 * (int)(info_block->bpp/8)));
  unsigned char* dst = (char *) ((uint64_t)(info_block->physbase + info_block->pitch * y1 + x1 * (int)(info_block->bpp/8)));
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}



/*
**Forma más eficiente de pintar chars, por cada fila del mapa de glyphs,
**se encarga de copiar "toda la fila entera" en vez de hacer putpixel
**de cada caracter.


void draw_char2(int x, int y) {
    char * where;
    mode_info_block* info_block = (mode_info_block *) get_info_block();
    where = (char *) ((uint64_t) info_block->physbase + x*info_block->bpp / 8 + (int) y*info_block->pitch);
    uint8_t row_data;
    uint32_t mask1, mask2;
    uint8_t foreground_colour = (WHITE.r << 16) + (WHITE.g << 8) + WHITE.b;

    uint8_t *font_data_for_char = &glyphs[0];
<<<<<<< HEAD
    uint32_t packed_foreground =
    (foreground_colour << 24) | (foreground_colour << 16) | (foreground_colour << 8) | foreground_colour;

=======
    uint32_t packed_foreground = (foreground_colour << 24) | (foreground_colour << 16) | (foreground_colour << 8) | foreground_colour;

>>>>>>> a1fab63791d540b769fe3e2cfef78aaf0593c778
    for (int row = 0; row < 16; row++) {
        row_data = font_data_for_char[row];
        mask1 = font_data_lookup_table[row_data / 16];
        mask2 = font_data_lookup_table[row_data & 0x0F];
        *(uint32_t *)where = (packed_foreground & mask1);
        *(uint32_t *)(&where[4]) = (packed_foreground & mask2);
        //where += x + (y << 8) + (y << 6);
        where += info_block->pitch;
    }
}*/
