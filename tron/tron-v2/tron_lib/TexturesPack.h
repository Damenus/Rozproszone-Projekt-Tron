#ifndef TexturesPack_h
#define TexturesPack_h
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"

//struktura na wszystkie textury
struct TexturesPack
{
public:


	//textury graczy	
	Texture player1Sprite;
	Texture player2Sprite;
	Texture player3Sprite;
	Texture player4Sprite;

	//textury ich œladów
	Texture player1TrailSprite;
	Texture player2TrailSprite;
	Texture player3TrailSprite;
	Texture player4TrailSprite;

	//textura planszy i paska bocznego
	Texture boardSprite;
	Texture sidebar;

	Texture background;


	//wczytanie wszystkich textur
	//metoda zwróci wyj¹tek (string), jak wystapi problem z wczytaniem
	void loadTextures(SDL_Renderer* winRenderer);

	//zwonlnienie textur
	void free();


}; 
typedef struct TexturesPack TexturesPack;

#endif