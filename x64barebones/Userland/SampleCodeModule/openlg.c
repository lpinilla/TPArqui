#include <openlg.h>
#include <syscall.h>

void shadow_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            sys_shadow_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void shadow_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            sys_shadow_pixel(j,i, r,g,b);
        }
    }
}

void swap_buffers(){
	sys_swap_buffers();
}
