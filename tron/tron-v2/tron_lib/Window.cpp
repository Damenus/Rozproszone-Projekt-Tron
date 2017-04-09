#define _CRT_SECURE_NO_WARNINGS
#include <SDL_ttf.h>

#include "Window.h"

//KONSTRUKTOR - inicjalizacja
//podajemy tytul okna i wymiary
Window::Window(const char * title,int width,int height)
{
	this->width = width;
	this->height = height;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	//obiekt okna
	if (window == NULL)
	{
		char ex[100];
		sprintf(ex, "Problem ze stworzeniem okna SDL Error: %s\n", SDL_GetError());
		throw ex;
	}


	//renderer dla okna z v sync
	//winRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//renderer dla okna bez v sync
	winRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (winRenderer == NULL)
	{
		char ex[100];
		sprintf(ex, "Problem z stworzeniem renderera: %s\n", SDL_GetError());
		throw ex;
	}

	//skala, ackzolwiek juz chyab nie potrzebne
	SDL_RenderSetScale(winRenderer, (double)width / (double)BASE_SCREEN_WIDTH, (double)height / (double)BASE_SCREEN_HEIGHT);
	//domyslny kolor
	SDL_SetRenderDrawColor(winRenderer, 0x11, 0x01, 0x11, 0xFF);

	windowRect = { 0, 0, height, width };


}


void Window::destroy()
{
	SDL_DestroyRenderer(winRenderer);
	SDL_DestroyWindow(window);
	window = NULL;
	winRenderer = NULL;
}

//czysczenie ekranu
void Window::clear()
{
	SDL_RenderClear(winRenderer);
}

//odœwie¿enie ekranu
void Window::update()
{
	SDL_RenderPresent(winRenderer);
}



void Window::renderTextureOnPosition(Texture *texture, int i, int j)
{
	int w =texture->getWidth();
	int h = texture->getHeight();
	SDL_Rect rect = { j*w, i*h, w, h };
	texture->render(&rect, winRenderer);
}

void Window::renderPlayers(Board *board)
{
	//wymiary tablicy
	int width = board->getWidth();
	int height = board->getHeight();
	
	//przechodzenie po planszy
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//jezeli pole rowna sie id gracza
			if (board->field[i][j] == PLAYER_1_NUM)
			{
				renderTextureOnPosition(&texPack.player1TrailSprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_2_NUM)
			{
				renderTextureOnPosition(&texPack.player2TrailSprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_3_NUM)
			{
				renderTextureOnPosition(&texPack.player3TrailSprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_4_NUM)
			{
				renderTextureOnPosition(&texPack.player4TrailSprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_1_CHAR)
			{
				renderTextureOnPosition(&texPack.player1Sprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_2_CHAR)
			{
				renderTextureOnPosition(&texPack.player2Sprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_3_CHAR)
			{
				renderTextureOnPosition(&texPack.player3Sprite, i, j);
			}
			else if (board->field[i][j] == PLAYER_4_CHAR)
			{
				renderTextureOnPosition(&texPack.player4Sprite, i, j);
			}
			
		}
	}

}

void Window::printTextOnScreen(std::string messege, int x, int y, int size, SDL_Color color)
{
	Texture text;
	//text.loadFromRenderedText(font, winRenderer, messege, color);
	TTF_Font *font = fontTron->GetFont(size);
	text.loadFromRenderedText(font, winRenderer, messege, color);
	
	SDL_Rect rectText = { x, y, text.getWidth(), text.getHeight() };
	text.render(&rectText, winRenderer);
	text.free();
	
}

void Window::printTextOnScreenCenteredHorizontally(std::string messege, int y, int size, SDL_Color color)
{
	Texture text;
	//text.loadFromRenderedText(font, winRenderer, messege, color);
	TTF_Font *font = fontTron->GetFont(size);
	text.loadFromRenderedText(font, winRenderer, messege, color);

	int x = (width - text.getWidth()) / 2;

	SDL_Rect rectText = { x, y, text.getWidth(), text.getHeight() };
	text.render(&rectText, winRenderer);
	text.free();
}


void Window::printTextOnScreenCentered(std::string messege, int size, SDL_Color color)
{
	Texture text;
	//text.loadFromRenderedText(font, winRenderer, messege, color);
	TTF_Font *font = fontTron->GetFont(size);
	text.loadFromRenderedText(font, winRenderer, messege, color);

	int x = (width - text.getWidth()) / 2;
	int y = (height - text.getHeight()) / 2;
	SDL_Rect rectText = { x, y, text.getWidth(), text.getHeight() };
	text.render(&rectText, winRenderer);
	text.free();
}


void Window::fillScreenWithColor(SDL_Color color)
{
	//soon


}


void Window::switchFullscreen()
{
	int w, h;
	if (!isFullscreen)
	{
		//zmien wyswietlanie na  pseudo-fullscreen
		SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//pobierz nowe wymiary
		SDL_GetWindowSize(window, &w, &h);

		//ustawienie skalowania
		SDL_RenderSetScale(winRenderer, (double)w / (double)(this->width), (double)h / (double)(this->height));

		isFullscreen = true;
		
	}
	else
	{
		//zmien wyswietlanie na "w oknie"
		SDL_SetWindowFullscreen(this->window, 0);
		//pobierz nowe wymiary
		SDL_GetWindowSize(window, &w, &h);

		//ustawienie skalowania
		SDL_RenderSetScale(winRenderer, (double)w / (double)(this->width), (double)h / (double)(this->height));

		isFullscreen = false;
	}
}