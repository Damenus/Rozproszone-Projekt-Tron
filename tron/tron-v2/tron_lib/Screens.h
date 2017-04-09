#ifndef Screen_h
#define Screens_h

#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Defines.h"
#include "TexturesPack.h"
#include "Window.h"
#include "Menu.h"


//Klasa abstrakcyjna dla ekranów
class Screen
{
	Window * parentWindow;
public:
	virtual void render() = 0;
};


//-------------GAME SCREEN
class ScreenGame : Screen
{
	const int boardX = BOARD_X;
	const int boardY = BOARD_Y;
	const int boardW = BOARD_WIDTH;
	const int boardH = BOARD_HEIGHT;

	const int sideBarX = BOARD_X + BOARD_WIDTH;
	const int sideBarY = BOARD_Y;
	const int sideBarW = BASE_SCREEN_WIDTH - BOARD_WIDTH;
	const int sideBarH = BOARD_HEIGHT;

	const int scorePositionX = SCORE_X;
	const int scorePositionY = SCORE_Y;
	SDL_Rect rectBg;
	SDL_Rect rectSb;

public:
	//okno do którego ten ekran nalezy
	Window *parentWindow = NULL;

public:
	//konstruktor
	ScreenGame(Window *win);
	//renderuj
	void render();
	//renderuj z punktami i z kolorami graczy
	void render(Board *board, int playerNum);
};


//---------------MAIN MENU---------------------

class ScreenMainMenu : Screen
{
	//oknko do którego ten ekran nalezy
	Window *parentWindow = NULL;
	Menu *mainMenu = NULL; 
	std::vector<std::string> menuList;

public:

	
	//renderowanie
	ScreenMainMenu(Window *win);

	////metoda nic nie robi
	virtual void render(){};

	//funkcja obs³ugi menu, wszelkie zmiany ekranów zapisuje
	//do przekazanego wskaŸnika na  gamemode
	//zwraca 1 jak wykryto event wyjœcia
	bool startMenu(enum gamemode &gmode, SDL_Event &e);
	
};


//--------------INPUT MENU----------------------
class ScreenInputIpMenu : Screen
{
	Window *parentWindow = NULL; //oknko do którego ten ekran nalezy
	Menu *inputMenu = NULL;
	std::vector<std::string> menuList;

public:


	//renderowanie
	ScreenInputIpMenu(Window *win);

	////metoda nic nie robi
	virtual void render(){};

	//funkcja obs³ugi menu, wszelkie zmiany ekranów zapisuje
	//do przekazanego wskaŸnika na gamemode
	//zwraca 1 jak wykryto event wyjœcia - generalnei jak chce sie wyjsc
	//ustala równie¿ ip (wczytuje od uzytkownika)
	bool startMenu(SDL_Event &e, std::string &ip);

};


class ScreenScoreBoard : Screen
{
	const int y = SCOREBOARD_Y;
	Window * parentWindow;

public:
	ScreenScoreBoard(Window *win);

	virtual void render(){};

	//renderuj z punktami
	void render(Board *board, int playerNum);
};



//---------------OPTIONS MENU---------------------
class ScreenOptionsMenu : Screen
{
	Window * parentWindow = NULL;
	Menu * optionsMenu = NULL;
	std::vector<std::string> menuList;

public:
	ScreenOptionsMenu(Window *win);

	virtual void render(){}

	bool startMenu(SDL_Event &e);
	
};



#endif