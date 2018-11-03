#include <graphics.h> //después cambiar para usar la librería de video
#include <keyboard.h>

#define PLAYER_SPEED 3
#define PLAYER_HEIGHT 120
#define PLAYER_WIDTH 25
#define PLAYER_TOP 30
#define PLAYER_BOTTOM 640
#define MAX_SCORE 3
#define SCORE_WIDTH 4
#define SCORE_HEIGHT 5
#define BALL_SIZE 20
#define BALL_SPEED 3 //4 para testar, 3 original y 5 para apurar el juego

enum STATE {GAME_OVER = 0,PLAYING };
enum DIRECTION {DOWN = 0, UP};
void draw_board(void);
void draw_game(void);
void draw_players(void);
void draw_scores(void);
void draw_player_n_score(int n, int x, int y);
void draw_ball();
void player_move(int n, enum DIRECTION dir);
void play(void);
void init_game(void);
void game_loop(void);
void player_score(int n);
void restart_game(void);

typedef struct{
	int x,y, score;
} player_position;

typedef struct{
	int x,y, down, right;
} ball_t;

//fin del .h

player_position players[2];
ball_t ball;

enum STATE game_state;
enum DIRECTION dir;


//se llama 1 sola vez para que limpie la pantalla y corra las demás cosas
void init_game(){
	players[0].score = players[1].score = 0;
	restart_game();
} 

void game_loop(){
	while(1){
		switch(game_state){
			case GAME_OVER:
				break;
			case PLAYING:
				play();
				move_ball();
				draw_game();
				break;
		}
	}
}

void draw_game(){
	draw_board(); //creo que esto se puede dibujar solo la primera vez
	draw_scores();
	draw_ball();
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

void draw_ball(){
	shadow_fill_square(ball.x, ball.y ,0xFF, 0xFF, 0xFF, BALL_SIZE);
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
							 0x0, 0x0, 0x0, PLAYER_WIDTH, PLAYER_SPEED);
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

void move_ball(){
	//ver si esta tocando algún borde
	//borde de arriba
	if(ball.y <= PLAYER_TOP){
		ball.down = 1;
	}
	//borde de abajo
	if(ball.y >= PLAYER_BOTTOM + PLAYER_HEIGHT - BALL_SIZE){
		ball.down = 0;
	}
	//movimientos
	if(ball.down){
		ball.y += BALL_SPEED;
		shadow_fill_rect(ball.x, ball.y - BALL_SPEED, 0x0, 0x0, 0x0, BALL_SIZE, BALL_SPEED);
	}else{
		ball.y -= BALL_SPEED;
		shadow_fill_rect(ball.x, ball.y + BALL_SIZE, 0x0, 0x0, 0x0, BALL_SIZE, BALL_SPEED);
	}
	if(ball.right){
		ball.x += BALL_SPEED;
		shadow_fill_rect(ball.x - BALL_SPEED, ball.y, 0x0, 0x0, 0x0, BALL_SPEED, BALL_SIZE);
	}else{
		ball.x -= BALL_SPEED;
		shadow_fill_rect(ball.x + BALL_SIZE, ball.y, 0x0, 0x0, 0x0, BALL_SPEED, BALL_SIZE);	
	}
	//colisiones
	//colisiona con alguna barra si la distancia desde el centro de la barra hasta la pelota
	//es menor o igual al tamaño del ancho de la barra

	//jugador de la izq
	if(ball.x >= 1 && ball.x <= PLAYER_WIDTH){
		if((ball.y >= players[0].y) && (ball.y <= (players[0].y + PLAYER_HEIGHT) )){
			if(ball.y <= (players[0].y + PLAYER_HEIGHT / 2)){
				ball.down = 0;
			}else{
				ball.down = 1;
			}
			ball.right = 1;
		}else{ //score
			player_score(1);
		}
	}else if(ball.x >= (999 - PLAYER_WIDTH)){
		if((ball.y >= players[1].y) && (ball.y <= (players[1].y + PLAYER_HEIGHT) )){
			if(ball.y >= players[1].y + PLAYER_HEIGHT / 2){
				ball.down = 0;
			}else{
				ball.down = 1;
			}
			ball.right = 0;
		}else{
			player_score(0);
		}
	}
}

void player_score(int player_n){
	//play_beep();
	if(players[player_n].score == MAX_SCORE){
		game_state = GAME_OVER;
		//llevar a pantalla de game_over;
	}else{
		players[player_n].score++;
		restart_game();
	}
}

void restart_game(){
	clear_screen();
	players[0].x = 1;
	players[1].x = 999;
	players[0].y = players[1].y = 300;
	ball.x = 550; //esto debería cambiar pedir tiempo de ms (hacer biblioteca rand?)
	ball.y = 300; //esto tambien
	ball.down = 0; //rand
	ball.right = 0; //rand
	game_state = PLAYING;	
	draw_game();
	game_loop();
}


char *numbers[SCORE_HEIGHT * 10] = {
	"1111",		//0
	"1001",
	"1001",
	"1001",
	"1111",
	"0001",		//1
	"0001",
	"0001",
	"0001",
	"0001",
	"1111",		//2
	"0001",
	"1111",
	"1000",
	"1111",
	"1111",		//3
	"0001",
	"1111",
	"0001",
	"1111",
	"1001",		//4
	"1001",
	"1111",
	"0001",
	"0001",
	"1111",		//5
	"1000",
	"1111",
	"0001",
	"1111",
	"1111",		//6
	"1000",
	"1111",
	"1001",
	"1111",
	"0111",		//7
	"0001",
	"0001",
	"0001",
	"0001",
	"1111",		//8
	"1001",
	"1111",
	"1001",
	"1111",
	"1111",		//9
	"1001",
	"1111",
	"0001",
	"0001",
};

void draw_scores(){
	draw_player_n_score(0, 350, 50);
	draw_player_n_score(1, 600, 50);
}

void draw_player_n_score(int player_n, int init_x, int init_y){	
	char * aux;
	int index = players[player_n].score * SCORE_HEIGHT;
	int t;
	for(int i = index, t = 0; i < index + SCORE_HEIGHT; i++, t++){
		aux = numbers[i];
		for(int j = 0; j < SCORE_WIDTH; j++){
			if(aux[j] == '1'){
				shadow_fill_square(init_x + 10 * j,init_y + 10 * t, 0xFF, 0xFF, 0xFF, 10);
			}else{
				shadow_fill_square(init_x + 10 * j,init_y + 10 * t, 0x0, 0x0, 0x0, 10);
			}
		}
	}
}
