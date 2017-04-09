#ifndef Font_h
#define Font_h
#include <map>
#include<SDL_ttf.h>


class Font
{
	std::string path;
	std::map<int, TTF_Font*> fonts;

public:

	Font();

	void load(std::string path);



	//zamknij czcionke
	static void close(TTF_Font *font);

	//zwraca czcionke o zadanym rozmiarze
	//je¿eli nie istnieje to stwarze now¹ i dodaje do mapy
	TTF_Font* GetFont(int FontSize);
	~Font();


};


#endif