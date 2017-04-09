#ifndef Defines_h
#define Defines_h

//wymairy okna
//#define SCREEN_WIDTH 1024
//#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//pierwotne
#define BASE_SCREEN_WIDTH 1280
#define BASE_SCREEN_HEIGHT 720

#define BOARD_WIDTH 960
#define BOARD_HEIGHT 720

#define DEBUG 0//1-debugowanie 0-normalnie


#define N 120 //wiersze
#define M 160 //kolumny



#define SCREEN_FPS  60
#define SCREEN_TICK_PER_FRAME  1000 / SCREEN_FPS

#define BOARD_X 0
#define BOARD_Y 0

#define PLAYERS_NUMBER 4

#define PLAYER_1_NUM 1
#define PLAYER_2_NUM 2
#define PLAYER_3_NUM 3
#define PLAYER_4_NUM 4

#define PLAYER_1_CHAR '@'
#define PLAYER_2_CHAR '#'
#define PLAYER_3_CHAR '$'
#define PLAYER_4_CHAR '%'

#define ALL_END 66 //wysy³ane jak wszyscy skoñcza runde
#define ALL_RUND_END 77//wysy³ane jak skoñcza siê rundy

#define SIDEBAR_X BOARD_X + BOARD_WIDTH
#define SIDEBAR_Y BOARD_Y
#define SIDEBAR_W BASE_SCREEN_WIDTH - BOARD_WIDTH
#define SIDEBAR_H BOARD_HEIGHT

#define SCORE_X SIDEBAR_X+40
#define SCORE_Y SIDEBAR_Y+20


#define SCOREBOARD_Y 100

#define RUNDS 5//Liczba rund


enum direction
{
	left,
	right,
	up,
	down,
	start,wait
};

enum gamemode  //lista ekranów
{
	mainmenu,		//menu g³ówne
	inputipmenu,	//menu wczytywania ip
	optionsmenu,	//menu opcji	
	waitforconnection, //czekanie na pod³aczenie
	failedConnection, //nie udalo sie po³¹czyæ
	game,			//gra
	gameover,		//ekran przegranej
	win,			//ekran wygranej
	nextround,		//ekran nastepnej rundy
	testgame,
	scoreboard		//ekran wyswietlajacy wyniki ostateczne
};

#endif

