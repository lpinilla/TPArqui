#include <graphics.h> //después cambiar para usar la librería de video

enum STATE {GAME_OVER = 0,PLAYING }; //tal vez agregar un estado más para cuando se carga por 1era vez

STATE game_state;

void draw_board(){
	//todo negro salvo la linea del medio
	memset()
}

//se llama 1 sola vez para que limpie la pantalla y corra las demás cosas
void init_game(){
	game_state = PLAYING;

} 