#ifndef Player_h
#define Player_h
#include "Texture.h"
#include "Defines.h"

class Player {
private:
	int id;
	int x;
	int y;
	int direction;		//kierunek ruchu
	int direction_x;	//w ktora strone horyzontalnie idze
	int direction_y;	//w ktora strone vertykalnie
						//obie wartosic przyjmuja 1,0 lub -1
	Texture vehicleTexture;	//tekstura pojazdu gracza
	Texture trailTexture;	//tekstura sladu; nie wiem cyz niepowinno sie track nazywac
	SDL_Rect * rect;	//prostokat opisujacy gracza

public:
	
	Player();

	Player(int id, int x, int y);

	~Player();

	void newPosition();

	//gety
	int getX();
	int getY();
	int getDirectionX();
	int getDirectionY();
	int getDirection();
	int getId();
	Texture getVehicleTexture();
	Texture * getTrailTexture();
	SDL_Rect * getRect();

	//sety
	void setX(int nowyx);
	void setY(int nowyy);
	void setDirectionX(int nowyx);
	void setDirectionY(int nowyy);
	void setDirection(int nowy);

	//metody
	bool loadVehTexture(std::string path, SDL_Renderer* winRenderer);	//wczytanie pojazdu
	bool loadTrailTexture(std::string path, SDL_Renderer* winRenderer);	//wczytanie sladu
	void renderVehicle(SDL_Renderer* winRenderer, double angle);		//renderowanie pojazdu gracza; angle - kat o jaki ma obrocic
	void renderTrail(SDL_Rect * rect, SDL_Renderer* winRenderer);						//renderowanie sladu gracza
	void freeTextures();
	void reset();

	
};
#endif