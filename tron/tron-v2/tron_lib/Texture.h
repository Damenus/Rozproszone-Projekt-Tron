#ifndef Texture_h
#define Texture_h

#include <SDL.h>
#include<SDL_ttf.h>

#include <string>

class Texture
{
public:
	
	Texture();

	//Gey
	int getWidth();
	int getHeight();

	//metody
	//zwolnienie powierzchni
	void free();
	//wczytanie textury z pliku
	bool loadFromFile(std::string path, SDL_Renderer* winRenderer);	
	//renderowanie na podstawie recta
	void render(SDL_Rect* rect, SDL_Renderer* winRenderer);		 
	//renderowanie na podstawie recta z obrotem o podany k¹t
	void render(SDL_Rect* rect, SDL_Renderer* winRenderer, double angle);
	//wczytanie textury z czcionki i podanego textu
	bool loadFromRenderedText(TTF_Font* font, SDL_Renderer* winRenderer, std::string textureText, SDL_Color textColor);	//do rysowania tekstur z tekstem


private:
	
	int width;
	int height;
	SDL_Texture* texture;
	
};

#endif