#ifndef _OPENLG_H_
#define _OPENLG_H_

void draw_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size);
void shadow_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size);
void shadow_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height);
void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height);

#endif