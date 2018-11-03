#include <graphics.h> //después cambiar para usar la librería de video
#include <keyboard.h>

#define PLAYER_SPEED 3
#define PLAYER_HEIGHT 120
#define PLAYER_WIDTH 25
#define PLAYER_TOP 30
#define PLAYER_BOTTOM 640
#define MAX_SCORE 3

enum STATE {GAME_OVER = 0,PLAYING }; //tal vez agregar un estado más para cuando se carga por 1era vez
enum DIRECTION {DOWN = 0, UP};
void draw_board(void);
void draw_game(void);
void draw_players(void);
void player_move(int n, enum DIRECTION dir);

typedef struct{
	int x,y;
} player_position;

player_position players[2];

enum STATE game_state;
enum DIRECTION dir;

int x_res, y_res; //resolutions

//se llama 1 sola vez para que limpie la pantalla y corra las demás cosas
void init_game(){

	players[0].x = 1;
	players[1].x = 999;
	players[0].y = players[1].y = 300;
	x_res = get_x_res();
	y_res = get_y_res();
	game_state = PLAYING;
	clear_screen();
	draw_game(); //esto en realidad no iría acá
	game_loop();
} 

void game_loop(){
	while(1){
		switch(game_state){
			case GAME_OVER:
				break;
			case PLAYING:
				play();
				draw_game();
				break;
		}
	}
}

void draw_game(){
	draw_board(); //creo que esto se puede dibujar solo la primera vez
	draw_players();
	swap_buffers(); //vblank;
}

//todo negro salvo la linea del medio
void draw_board(){
	for(int i = 0; i < 12; i++){
		shadow_fill_rect( 90 * i, 20, 0xFF, 0xFF, 0xFF, 30, 10);	
	}
	for(int i = 0; i < 10; i++){
		shadow_fill_rect(500, 20 + 90 * i, 0xFF, 0xFF, 0xFF, 15, 30);	
	}
	for(int i = 0; i < 12; i++){
		shadow_fill_rect( 90 * i, 760, 0xFF, 0xFF, 0xFF, 30, 10);	
	}
}

void draw_players(){
	shadow_fill_rect(players[0].x, players[0].y, 0xFF, 0xFF, 0xFF, PLAYER_WIDTH, PLAYER_HEIGHT);
	shadow_fill_rect(players[1].x, players[1].y, 0xFF, 0xFF, 0xFF, PLAYER_WIDTH, PLAYER_HEIGHT);
}

void player_move(int player_n, enum DIRECTION dir){
	for(int i = 0; i < 10 ; i++){
		if(dir == DOWN && players[player_n].y <= PLAYER_BOTTOM){
			players[player_n].y += PLAYER_SPEED;
			shadow_fill_rect(players[player_n].x, players[player_n].y - PLAYER_SPEED * 2,
							 0x0, 0x0, 0x0, PLAYER_WIDTH, PLAYER_SPEED);
		}else if(dir == UP && players[player_n].y >= PLAYER_TOP){
			players[player_n].y -= PLAYER_SPEED;
			shadow_fill_rect(players[player_n].x, players[player_n].y + PLAYER_HEIGHT,
							 0x0, 0x00, 0x0, PLAYER_WIDTH, PLAYER_SPEED);
		}
	}
}

void play(){
	char c = get_char();
	switch(c){
		case 'w':
			player_move(0, UP);
			break;
		case 's':
			player_move(0, DOWN);
			break;
		case 'p':
			player_move(1, UP);
			break;
		case 'l':
			player_move(1, DOWN);
			break;
		default:
			break;
	}
}