#include "TexturesPack.h"
#include <string>

void TexturesPack::loadTextures(SDL_Renderer* winRenderer)
{

	std::string exception;

	//wczytanie textur gracza
	//jezeli loadFromFile zwróci false (nie uda³o siê)
	//wyrzyæ wyj¹tek

	if (!(this->player1Sprite.loadFromFile("spr/player1.png", winRenderer)))
	{
		exception = "problem z wczytaniem player1.png";
		throw exception;
	}

	if (!(this->player2Sprite.loadFromFile("spr/player2.png", winRenderer)))
	{
		exception = "problem z wczytaniem player2.png";
		throw exception;
	}
	if (!(this->player3Sprite.loadFromFile("spr/player3.png", winRenderer)))
	{
		exception = "problem z wczytaniem player3.png";
		throw exception;
	}
	if (!(this->player4Sprite.loadFromFile("spr/player4.png", winRenderer)))
	{
		exception = "problem z wczytaniem player4.png";
		throw exception;
	}

	//wczytanie textur œlaów gracza

	if (!(this->player1TrailSprite.loadFromFile("spr/player1trail.png", winRenderer)))
	{
		exception = "problem z wczytaniem player1trail.png";
		throw exception;
	}

	if (!(this->player2TrailSprite.loadFromFile("spr/player2trail.png", winRenderer)))
	{
		exception = "problem z wczytaniem player2trail.png";
		throw exception;
	}
	if (!(this->player3TrailSprite.loadFromFile("spr/player3trail.png", winRenderer)))
	{
		exception = "problem z wczytaniem player3trail.png";
		throw exception;
	}
	if (!(this->player4TrailSprite.loadFromFile("spr/player4trail.png", winRenderer)))
	{
		exception = "problem z wczytaniem player4trail.png";
		throw exception;
	}

	//wczytanie elementów ekranu
	
	if (!(this->boardSprite.loadFromFile("spr/boardSprite.gif", winRenderer)))
	{
		exception = "problem z wczytaniem boardSprite.gif";
		throw exception;
	}

	if (!(this->sidebar.loadFromFile("spr/sidebar.png", winRenderer)))
	{
		exception = "problem z wczytaniem sidebar.png";
		throw exception;
	}

	if (!(this->background.loadFromFile("spr/background.png", winRenderer)))
	{
		exception = "problem z wczytaniem background.png";
		throw exception;
	}


}


void TexturesPack::free()
{
	player1Sprite.free();
	player2Sprite.free();
	player3Sprite.free();
	player4Sprite.free();

	player1TrailSprite.free();
	player2TrailSprite.free();
	player3TrailSprite.free();
	player4TrailSprite.free();

	boardSprite.free();
	sidebar.free();

	background.free();


}