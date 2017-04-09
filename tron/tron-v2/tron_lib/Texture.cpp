#include "Texture.h"
#include <stdio.h>
#include <SDL_image.h>
Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}



bool Texture::loadFromFile(std::string path,SDL_Renderer* winRenderer)
{
	//usuñ poprzednia
	free();

	//wcyztaj powierzchnie ze œcie¿ki
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Nie mo¿na wczytac obrazu %s: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Klucz na kolor, ale wczytujemy png wiec nei trzeba
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0x00, 0x90));

		//tworzenie tekstury z powierzchni
		texture = SDL_CreateTextureFromSurface(winRenderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Problem z stworzeniem tekstury %s: %s", path.c_str(), SDL_GetError());
		}
		else
		{
			//wczytaj wymiary
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//zwolnij powierzchnie
		SDL_FreeSurface(loadedSurface);
	}


	//jak niezerowa to sie udalo
	if (texture != NULL)
		return true;
	else
		return false;
}

void Texture::free()
{
	//jak istnieje to zwolnij
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(SDL_Rect* rect, SDL_Renderer* winRenderer)
{
	SDL_RenderCopyEx(winRenderer, texture, NULL, rect, NULL, NULL, SDL_FLIP_NONE);
}



void Texture::render(SDL_Rect* rect, SDL_Renderer* winRenderer,double angle)
{
	SDL_RenderCopyEx(winRenderer, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE); //NULL, bo to jest Ÿró³owy rect, ale my piszemy do recta playera
}


int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}


bool Texture::loadFromRenderedText(TTF_Font* font, SDL_Renderer* winRenderer, std::string textureText, SDL_Color textColor)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		
		texture = SDL_CreateTextureFromSurface(winRenderer, textSurface);
		if (texture == NULL)
		{
			printf("Problem ze stworzeniem textury z tekstu: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	if (texture != NULL)
		return true;
	else
		return false;
}
