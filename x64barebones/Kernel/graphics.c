#include <stdio.h>
#include <stdint.h>
#include <string.h>
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



void draw_welcome_screen(){
  //clear_screen();
  new_line();
  new_line();
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
  //mensaje de bienvenida
  for(int i = 0; i < 9; i++){
    draw_string(title[i]);
    new_line();
  }
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

<<<<<<< HEAD
=======
//se puede especificar color de frente y de fondo
void draw_char_w_front_and_back_color(int x, int y, char c, int r, int g, int b, int r2, int g2, int b2){
  if(c=='\n')
    return new_line();
  if(c=='\b')
    return erase_character();
  if(x_cursor >= get_x_res()){
    x_cursor = 0;
    if(y_cursor >= get_y_res() - CHAR_HEIGHT){
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
>>>>>>> 526d47a5772574140a7180bc72fd61c69fb15f26

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

//testeable
int number_of_digits(int n){
  if(n == 0)  return 0;
  return 1 + number_of_digits(n/10);
}

//verificar los límites
void erase_character(){
  if(x_cursor == 0){
    if(y_cursor == 0){
      draw_color_char(' ', 0xFF,0xFF,0xFF);
    }else{
      y_cursor -= CHAR_HEIGHT;
      x_cursor = get_x_res() - CHAR_WIDTH;
      draw_color_char(' ', 0xFF,0xFF,0xFF);
    }
  }else{
    x_cursor -= CHAR_WIDTH;
    draw_color_char(' ', 0xFF,0xFF,0xFF);
  }
  x_cursor -= CHAR_WIDTH;
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

void new_line(){
  if(y_cursor != get_y_res()){
    y_cursor += CHAR_HEIGHT;
  }else{
    move_everything_up();
  }
  x_cursor = 0;
}

//se puede especificar color de frente y de fondo
void draw_char_w_front_and_back_color(int x, int y, char c, int r, int g, int b, int r2, int g2, int b2){
  if(x_cursor >= get_x_res()){
    x_cursor = 0;
    if(y_cursor >= get_y_res() - CHAR_HEIGHT){
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

//-------------------------------------HARDWARE

void init_graphics(){
  info_block = (mode_info_block*)0x0000000000005C00;
  draw_welcome_screen();
}

void draw_pixel(int x, int y, int r, int g, int b) {
	screen = (unsigned char *) ((uint64_t) info_block->physbase + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

void shadow_pixel(int x, int y, int r, int g, int b) {
  screen = (unsigned char *) ((uint64_t) shadow_buffer + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}


//limpiar la pantalla principal
void clear_screen(){
  memset((char *) ((uint64_t) info_block->physbase), 0, info_block->y_res * info_block->x_res * info_block->bpp/8);
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
  //memset(shadow_buffer, 0x0, sizeof(shadow_buffer));
  //swap_buffers();
}

//limpiar todo el buffer auxiliar
void clear_shadow_buffer(){
  memset(shadow_buffer, 0x0, sizeof(shadow_buffer));
}


void move_everything_up(){
  memcpy((char *) ((uint64_t) info_block->physbase), (char *) ((uint64_t) info_block->physbase + info_block->pitch * CHAR_HEIGHT),
           (info_block->x_res * info_block->bpp / 8 * CHAR_WIDTH * 2) * info_block->y_res / CHAR_HEIGHT);
}

//si no anda bien, copiar la cantidad de bytes del move_everything_up
void swap_buffers(){
  memcpy((char *) ((uint64_t) info_block->physbase - info_block->pitch * CHAR_HEIGHT), (char *) shadow_buffer,
         (uint64_t) info_block->x_res * info_block->y_res * info_block->bpp/8);
}


int get_x_res(){
  return info_block->x_res;
}

int get_y_res(){
  return info_block->y_res;
}
