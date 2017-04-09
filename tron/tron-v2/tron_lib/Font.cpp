#include "Font.h"


Font::Font()
{
	this->path = "";

}

void Font::load(std::string path)
{
	//spr czy œciezka jest poprawna
	TTF_Font *font = TTF_OpenFont(path.c_str(), 10);
	if (font == NULL)
	{
		std::string exception = "Problem z wczytaniem czcionki ";
		exception += path;
		throw exception;
	}
	this->path = path;
	fonts.insert(std::pair<int, TTF_Font*>(10, font));
}

//zamykanie fontu
void Font::close(TTF_Font *font)
{
	TTF_CloseFont(font);
}

TTF_Font* Font::GetFont(int fontSize)
{
	//moze trzeba daæ insert na poc¿atku - jak jest to i tak nie da;
	//iterator
	if (fonts.empty())
	{
		TTF_Font* mFont = TTF_OpenFont(path.c_str(), fontSize);
		fonts.insert(std::pair<int, TTF_Font*>(fontSize, mFont));
		return mFont;
	}
	else
	{
		std::map<int, TTF_Font*>::iterator it;
		it = fonts.find(fontSize);

		if (it != fonts.end())
			return it->second;
		else
		{
			TTF_Font* mFont = TTF_OpenFont(path.c_str(), fontSize);
			fonts.insert(std::pair<int, TTF_Font*>(fontSize, mFont));
			return mFont;
		}
	}
	
}

Font::~Font()
{
	//dla kazdego elementu mapy zamknij czcionke
	for (auto i : fonts)
	{
		TTF_CloseFont(i.second);
	}

}