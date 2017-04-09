#include "Menu.h"


Menu::Menu(Window *parentWindow, std::vector<std::string>list, SDL_Color textColor, SDL_Color selectedColor, int fontSize, int space)
{	
	this->parentWindow = parentWindow;
	this->textColor = textColor;
	this->selectedColor = selectedColor;	
	this->fontSize = fontSize;
	this->spaceBetween = space;
	dx = 0;
	dy = 0;
	selectedPosition = 0;
	
	//wczytanie wymiarów tekstów
	int w, h;
	for (auto text : list)
	{
		TTF_SizeText(parentWindow->fontTron->GetFont(fontSize), text.c_str(), &w, &h);
		fieldList.push_back(new Field(text, w, h));
	}

	this->fieldNumber = fieldList.size();

	//ustalenie wymiarów menu
	height = 0;
	width = 0;
	for (auto field : fieldList)
	{
		//jezeli nie ostatni element
		//to dodaj do wymiaru h jeszcze odleglosc miêdzy elementami
		if (field != fieldList.at(fieldList.size() - 1))
			field->h += spaceBetween;
		

		height += field->h;		

		if (field->w > width)
			width = field->w;
	}
	
	//ustalenie pozycji menu i poszczególnym jego elementów
	int screenW = parentWindow->getWidth();
	int screenH = parentWindow->getHeight();

	this->x = (screenW - width) / 2;
	this->y = (screenH - height) / 2;

	int i = 0, tempY=y;
	for (auto field : fieldList)
	{
		field->x = (width - field->w) / 2 + x;
		field->y = tempY;
		tempY += field->h;
	}

	fieldList.at(0)->selected = true;


}

//2-gi konstruktor
Menu::Menu(Window *parentWindow, std::vector<std::string>list, SDL_Color textColor, SDL_Color selectedColor, int fontSize, int space, int dx, int dy)
{


	this->parentWindow = parentWindow;
	this->textColor = textColor;
	this->selectedColor = selectedColor;
	this->fontSize = fontSize;
	this->spaceBetween = space;
	this->dx = dx;
	this->dy = dy;
	selectedPosition = 0;

	//wczytanie wymiarów tekstów
	int w, h;
	for (auto text : list)
	{
		TTF_SizeText(parentWindow->fontTron->GetFont(fontSize), text.c_str(), &w, &h);
		fieldList.push_back(new Field(text, w, h));
	}

	this->fieldNumber = fieldList.size();

	//ustalenie wymiarów menu
	height = 0;
	width = 0;
	for (auto field : fieldList)
	{
		//jezeli nie ostatni element
		//to dodaj do wymiaru h jeszcze odleglosc miêdzy elementami
		if (field != fieldList.at(fieldList.size() - 1))
			field->h += spaceBetween;


		height += field->h;

		if (field->w > width)
			width = field->w;
	}

	//ustalenie pozycji menu i poszczególnym jego elementów
	int screenW = parentWindow->getWidth();
	int screenH = parentWindow->getHeight();

	this->x = (screenW - width) / 2;
	this->y = (screenH - height) / 2;

	int i = 0, tempX = x + dx, tempY = y + dy;
	for (auto field : fieldList)
	{
		field->x = (width - field->w) / 2 + tempX;
		field->y = tempY;
		tempY += field->h;
	}

	fieldList.at(0)->selected = true;


}






int Menu::render(int move)
{
	//jezeli jest przesuniecie
	if (move)
	{
		fieldList.at(selectedPosition)->selected = false;
		//dodaj do aktualnej pozycji
		this->selectedPosition += move;
		
		//jezeli pozycja jest ujemna - przenies na koniec
		if (selectedPosition == -1)
			selectedPosition = fieldNumber - 1;

		//modulo - bo jezeli mam 3 pola, to przy zjezdzaniu w dol jak dojdziemy 
		//ponad to co mamy to modulo zwroci 1 
		//np mamy 3 pola, zjezdzamy w dol, selectedposition = 4, a 3%4 == 1 wiec wracamy do góry
		selectedPosition %= fieldNumber;

		fieldList.at(selectedPosition)->selected = true;

	}
		for (auto field : fieldList)
		{
			if (field->selected)
				parentWindow->printTextOnScreen(field->text, field->x, field->y,fontSize,selectedColor);
			else
				parentWindow->printTextOnScreen(field->text, field->x, field->y, fontSize, textColor);
		}


		return selectedPosition;


	
}

std::string Menu::staticRender()
{
	return this->fieldList.at(render())->text;
}

int Menu::renderUp()
{
	return render(-1);
}
int Menu::renderDown()
{
	return render(1);
}


std::string Menu::moveUp()
{
	return this->fieldList.at(render(-1))->text;
}
std::string Menu::moveDown()
{
	return this->fieldList.at(render(1))->text;
}

void Menu::resetMenu()
{
	this->selectedPosition = 0;

	for (auto field : fieldList)
	{
		field->selected = false;
	}

	fieldList.at(0)->selected = true;
}



void Menu::changeFields(std::vector<std::string>list)
{
	fieldList.clear();
	//wczytanie wymiarów tekstów
	int w, h;
	for (auto text : list)
	{
		TTF_SizeText(parentWindow->fontTron->GetFont(fontSize), text.c_str(), &w, &h);
		fieldList.push_back(new Field(text, w, h));
	}

	this->fieldNumber = fieldList.size();

	//ustalenie wymiarów menu
	height = 0;
	width = 0;
	for (auto field : fieldList)
	{
		//jezeli nie ostatni element
		//to dodaj do wymiaru h jeszcze odleglosc miêdzy elementami
		if (field != fieldList.at(fieldList.size() - 1))
			field->h += spaceBetween;


		height += field->h;

		if (field->w > width)
			width = field->w;
	}

	//ustalenie pozycji menu i poszczególnym jego elementów
	int screenW = parentWindow->getWidth();
	int screenH = parentWindow->getHeight();

	this->x = (screenW - width) / 2;
	this->y = (screenH - height) / 2;

	int i = 0, tempY = y;
	for (auto field : fieldList)
	{
		field->x = (width - field->w) / 2 + x;
		field->y = tempY;
		tempY += field->h;
	}

	fieldList.at(0)->selected = true;
}