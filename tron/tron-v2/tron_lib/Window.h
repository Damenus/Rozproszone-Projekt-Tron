#ifndef Window_h
#define Window_h

#include <SDL.h>
#include "Texture.h"
#include "Defines.h"
#include "TexturesPack.h"
#include "Board.h"
#include "Font.h"


class Window
{
private:
	int width;
	int height;
public:

	bool isFullscreen = false;
	SDL_Window* window = NULL;			//wskaznik na okno
	SDL_Renderer* winRenderer = NULL;	//tzw renderer - on rysuje w oknie
	SDL_Rect windowRect;
	TexturesPack texPack;				//struktura z texturami
	Font *fontTron = NULL;

	Window(const char * title, int width, int height);

	//rysowanie na podstawie planszy
	void renderPlayers(Board *board);

	//wypisz text na ekranie
	//messege - text do wypisania, x,y - wspó³rzêdne, size -rozmiar czcionki, color - kolor napisu
	void printTextOnScreen(std::string messege, int x, int y, int size, SDL_Color color);

	//wypisz text na ekranie wysrodkowany pionowo
	void printTextOnScreenCenteredHorizontally(std::string messege, int y, int size, SDL_Color color);

	//wypisz text na ekranie wysrodkowany
	void printTextOnScreenCentered(std::string messege, int size, SDL_Color color);

	//rysuj zadan¹ texturê na pozycji podajen z tablicy
	void renderTextureOnPosition(Texture *texture, int i, int j);
	
	//czysczenie ekranu
	void clear();

	//odœwie¿enie ekranu
	void update();

	//zniszczenie okna
	void destroy();	

	//wypie³nij kolorem
	void fillScreenWithColor(SDL_Color color);

	//zmiana wyswietlania na pelny ekran
	void switchFullscreen();

	

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}
};


#endif