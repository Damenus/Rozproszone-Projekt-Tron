#ifndef Menu_h
#define Menu_h
#include <vector>	//podobno vector jest lepszy na ma³¹ ilosæ danych
#include<SDL.h>
#include <SDL_ttf.h>
#include"Window.h"
#include"Texture.h"

//klasa dla menu
//domyœlnie wyœrodkowane
class Menu
{
	class Field
	{
	public:
		std::string text;
		int w;
		int h;
		int x;
		int y;
		bool selected;
		int space;

		Field(std::string text, int w, int h)
		{
			this->text = text; this->w = w; this->h = h;
			selected = false;
			x = 0;
			y = 0;
		}

		bool operator==(const Field& right)
		{
			return text.compare(right.text);
		}

	};
	
	std::vector<Field*> fieldList; //wektor z obiektami textow menu
	int fieldNumber;
	Texture bgTexture;
	Window *parentWindow;
	SDL_Color textColor;
	SDL_Color selectedColor;
	int fontSize;
	int spaceBetween; //odlegloœæ miêdzy elementami menu

	//od 0 do fieldNumber-1
	int selectedPosition;

	//pozycja
	int x;
	int y;

	//wymiary menu
	int height;
	int width;

	//przesuniecie od srodka
	int dx;
	int dy;

	
	
public:
	Menu(Window *parentWindow, std::vector<std::string>list, SDL_Color textColor, SDL_Color selectedColor, int fontSize, int space);
	//dx,dy - przesuniêcie od œrodka
	Menu(Window *parentWindow, std::vector<std::string>list, SDL_Color textColor, SDL_Color selectedColor, int fontSize, int space, int dx, int dy);

	//zmien pola menu
	void changeFields(std::vector<std::string>list);

	//renderuj
	//zwraca wybrana pozycje
	int render(int move = 0);

	//wyrenderowanie bez przesuniêcia
	//zwraca aktualnie wybrana pozycje (czyli pocz¹tkow¹)
	std::string staticRender();

	//renderuje menu z zaznaczeniem przesuniêtym w góre
	//zwraca aktualnie wybrana pozycje
	int renderUp();
	//renderuj menu z zaznaczeniem przesuniêtym w góre
	int renderDown();


	//renderuje menu z zaznaczeniem przesuniêtym w góre
	//zwraca aktualnie wybrana pozycje w postaci stringa
	std::string moveUp();
	//renderuje menu z zaznaczeniem przesuniêtym w góre
	//zwraca aktualnie wybrana pozycje w postaci stringa
	std::string moveDown();

	//ustawia pozycje wybranego na 0
	void resetMenu();

};
#endif Menu