#include <graphics.h> //después cambiar para usar la librería de video

enum STATE {GAME_OVER = 0,PLAYING, INIT }; //tal vez agregar un estado más para cuando se carga por 1era vez
void draw_board(void);
void draw_game(void);
void draw_players(void);

enum STATE game_state;
int x_res, y_res; //resolutions

//se llama 1 sola vez para que limpie la pantalla y corra las demás cosas
void init_game(){
	x_res = get_x_res();
	y_res = get_y_res();
	game_state = PLAYING;
	clear_screen();
	draw_game(); //esto en realidad no iría acá
} 

void game_loop(){
	while(1){
		switch(game_state){
			case GAME_OVER:
				break;
			case PLAYING:

				break;
		}
	}
}

void draw_game(){
	draw_board();
	draw_players();
	swap_buffers();
}

//todo negro salvo la linea del medio
void draw_board(){
	for(int i = 0; i < 10; i++){
		shadow_fill_rect(500, 20 + 90 * i, 0xFF, 0xFF, 0xFF, 15, 30);	
	}
}

void draw_players(){
	shadow_fill_rect(0, 300, 0xFF, 0xFF, 0xFF, 25, 125);
	shadow_fill_rect(1000, 300, 0xFF, 0xFF, 0xFF, 25, 125);
}