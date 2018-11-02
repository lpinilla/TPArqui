#include <stdio.h>
#include <stdint.h>
#include <graphics.h>
#include <bitmap.h>
#include <glyphs.h>

//resolucion 1024*768

//-----------------Variables locales
unsigned char * screen; //se usa para no estar creandolo todo el tiempo
static char shadow_buffer[64] = {'0'}; //64k = 320 * 200
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
  //podría mostrar mensaje de bienvenida
}


void draw_pixel(int x, int y, int r, int g, int b) {
	screen = (char *) ((uint64_t) info_block->physbase + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

void shadow_pixel(int x, int y, int r, int g, int b) {
  screen = (char *) ((uint64_t) shadow_buffer + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

//para mi deben ser funciones separadas porque el double buffering es opcional, el que lo conoce
//y lo quiere usar, que use los métodos específicos.

void shadow_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            shadow_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            draw_pixel(j,i, r,g,b);
        }
    }
}

void shadow_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            shadow_pixel(j,i, r,g,b);
        }
    }
}

//se puede especificar color de frente y de fondo
void draw_char_w_front_and_back_color(int x, int y, char c, int r, int g, int b, int r2, int g2, int b2){
  if(x_cursor >= info_block->x_res){
    x_cursor = 0;
    if(y_cursor >= info_block->y_res - CHAR_HEIGHT){
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
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,r2,g2,b2); //necesito esto para poder borrar
      }
    }
  }
  x_cursor += CHAR_WIDTH;
}

//vos le especificas color de frente y de fondo
void draw_free_char(char c, int front_r, int front_g, int front_b, int back_r, int back_g, int back_b){
  draw_char_w_front_and_back_color(x_cursor, y_cursor, c, front_r, front_g, front_b, back_r, back_g, back_b);
}

//vos le especificas los colores de frente y de fondo
void draw_free_string(char * string, int front_r, int front_g, int front_b, int back_r, int back_g, int back_b){
  int i = 0;
  while(*(string + i)){
    draw_free_char(string[i++], front_r, front_g, front_b, back_r, back_g, back_b);
  } 
}

//vos solo elegis color de frente (fondo negro)
void draw_color_char(char c, int r, int g, int b){
  draw_char_w_front_and_back_color(x_cursor, y_cursor, c, r, g, b, 0x0, 0x0, 0x0);
}

//clasico, fondo negro letras blancas
void draw_char(char c){
  draw_free_char(c, 0XFF, 0XFF, 0XFF, 0x0, 0x0, 0x0);
}

void draw_string(char * string){
  draw_free_string(string, 0xFF, 0XFF, 0XFF, 0x0,0x0,0x0);
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
      draw_color_char(' ', 0xFF,0xFF,0xFF);
    }else{
      y_cursor -= CHAR_HEIGHT;
      x_cursor = info_block->x_res - CHAR_WIDTH;
      draw_color_char(' ', 0xFF,0xFF,0xFF);
    }
  }else{
    x_cursor -= CHAR_WIDTH;
    draw_color_char(' ', 0xFF,0xFF,0xFF);
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
  //memset(info_block->physbase, 0, info_block->y_res * info_block->x_res * info_block->bpp/8);
  memset(shadow_buffer, 0, 64 * sizeof(char));
  swap_buffers();
}

void new_line(){
  if(y_cursor != info_block->y_res){
    y_cursor += CHAR_HEIGHT;
  }else{
    move_everything_up();
  }
  x_cursor = 0;
}

void move_everything_up(){
  memcpy(info_block->physbase, info_block->physbase + info_block->pitch * CHAR_HEIGHT,
           (info_block->x_res * info_block->bpp / 8 * CHAR_WIDTH * 2) * info_block->y_res / CHAR_HEIGHT);
}

//si no anda bien, copiar la cantidad de bytes del move_everything_up
void swap_buffers(){
  memcpy(info_block->physbase - info_block->pitch * CHAR_HEIGHT, shadow_buffer,
         info_block->x_res * info_block->y_res * info_block->bpp/8);
}

int get_x_res(){
  return info_block->x_res;
}

int get_y_res(){
  return info_block->y_res;
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
