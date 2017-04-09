#include "Screens.h"
#include "DefinesSDL.h"
#include <regex> 
#include <vector>


//--------------SCREEN GAME-------------
ScreenGame::ScreenGame(Window *win)
{
	parentWindow = win;
	rectBg = { boardX, boardY, boardW, boardH };
	rectSb = { sideBarX, sideBarY, sideBarW, sideBarH };
}

void ScreenGame::render()
{
	parentWindow->texPack.boardSprite.render(&rectBg, parentWindow->winRenderer);
	parentWindow->texPack.sidebar.render(&rectSb, parentWindow->winRenderer);
}

void ScreenGame::render(Board *board, int playerNum)
{

	//rysuj plansze i sidebar
	parentWindow->texPack.boardSprite.render(&rectBg, parentWindow->winRenderer);
	parentWindow->texPack.sidebar.render(&rectSb, parentWindow->winRenderer);

	//wypisz texty punktow
	parentWindow->printTextOnScreen("Points:", scorePositionX, scorePositionY, 60, WHITE);

	//kolejne wspolrzedna dla napisow
	int y,x = scorePositionX;
	std::string text = "";

	for (int i = 1; i < PLAYERS_NUMBER + 1; i++)
	{
		y = scorePositionY - 10 + i * 50;
		//jezeli i to numer gracza, wypisz "YOU" zamiast "player"
		if (i == playerNum)
			text = std::string("YOU: ") + std::to_string(board->score[i - 1]);
		else
			text = std::string("PLAYER_") + std::to_string(i) + std::string(": ") + std::to_string(board->score[i - 1]);

		//wypisz na ekranie
		parentWindow->printTextOnScreen(text, x, y, 80, PLAYER_COLORS[i - 1]);
	}


}


//------------SCREEN MENU-----------------

ScreenMainMenu::ScreenMainMenu(Window *win)
{	
	parentWindow = win;

	menuList = { "Start", "Options", "Exit" };
	////MENU TEST
	this->mainMenu = new Menu(parentWindow, menuList, { 100, 100, 100, 255 }, { 255, 255, 255, 255 }, 150, 10);

}

bool ScreenMainMenu::startMenu(enum gamemode &gmode, SDL_Event &e)
{
	//inicjalizacja zmiennych, resetowanie menu
	bool exit = false;
	//int position;
	std::string position = "";
	mainMenu->resetMenu();

	//wyswietlenie menu 
	parentWindow->clear();
	position = mainMenu->staticRender();
	parentWindow->update();

	//petla g³owna
	while (true)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT)
			{
				return true;
			}//obs³uga klawiatury
			else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
			{
				switch (e.key.keysym.sym)
				{//obs³uga strza³kami
				case SDLK_UP:					
					parentWindow->clear();
					position = mainMenu->moveUp();
					break;
				case SDLK_DOWN:
					parentWindow->clear();
					position = mainMenu->moveDown();
					break;
				case SDLK_SEMICOLON:
					parentWindow->clear();
					parentWindow->update();
					gmode = scoreboard;
					return false;
				case SDLK_RETURN:
					if (position.compare(menuList.at(0)) == 0)
					{
						//wyczyœæ okno, zmieñ gamemoda na input menu
						parentWindow->clear();
						parentWindow->update();
						gmode = inputipmenu;
						return false;
					}
					else if (position.compare(menuList.at(1)) == 0)
					{
						//wyczyœæ okno, zmieñ gamemoda na input menu
						parentWindow->clear();
						parentWindow->update();
						gmode = optionsmenu;
						return false;
					}
					else if (position.compare(menuList.at(2)) == 0)
					{
						//zwróæ true, co równoznaczy sie z wyjœciem z programu
						return true;
					}
						
					break;
				default:
					break;

				}
			}
		}
		parentWindow->update();

		

	}
	return false;
}


//-----------------------SCREEN INPUT--------------

ScreenInputIpMenu::ScreenInputIpMenu(Window *win)
{
	parentWindow = win;

	menuList = { "Start game", "Back" };
	////MENU TEST
	this->inputMenu = new Menu(parentWindow, menuList, { 100, 100, 100, 255 }, { 255, 255, 255, 255 }, 150, 10, 0, 100);

}



bool ScreenInputIpMenu::startMenu(SDL_Event &e, std::string &ip)
{
	std::regex ipPattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
	//inicjalizacja zmiennych, resetowanie menu
	bool exit = false;
	//int position;
	std::string position = "";
	inputMenu->resetMenu();

	//wyswietlenie menu pierwszy raz
	parentWindow->clear();
	parentWindow->printTextOnScreenCenteredHorizontally("Please input IP of server", 100, 60, WHITE);
	position = inputMenu->staticRender();
	parentWindow->update();
	
	//odpalamy wczytywanie textu
	SDL_StartTextInput();
	bool renderText = false;



	//petla g³owna
	while (true)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT)
			{
				ip = "";
				SDL_StopTextInput();
				return true;
			}//obs³uga klawiatury
			else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
			{

				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					//zwróæ true, co równoznaczy sie z wyjœciem z programu
					ip = "";
					SDL_StopTextInput();
					return true;
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{

					parentWindow->clear();
					position = inputMenu->moveUp();
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					parentWindow->clear();
					position = inputMenu->moveDown();
				}
				else if (e.key.keysym.sym == SDLK_RETURN)
				{
					//if (position.compare("Start game") == 0)
					if (position.compare(menuList.at(0)) == 0)
					{

						//jezeli ip jest Ÿle podane
						if (!std::regex_match(ip, ipPattern))
						{
							parentWindow->printTextOnScreenCenteredHorizontally("Wrong format of ip", 100, 60, WHITE);
							parentWindow->update();
							renderText = false;
							continue;
						}


						//wyczyœæ okno, zmieñ gamemoda na input menu
						parentWindow->clear();
						parentWindow->update();

						SDL_StopTextInput();
						return false;
					}
					else if (position.compare(menuList.at(1)) == 0)
					{
						ip = "";
						//zwróæ true, co równoznaczy sie z wyjœciem z programu
						parentWindow->clear();
						parentWindow->update();
						SDL_StopTextInput();
						return true;
					}					

				
				}
			}
			else if (e.key.keysym.sym == SDLK_BACKSPACE && ip.length() > 0)
			{
				//lop off character
				ip.pop_back();
				renderText = true;
			}
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) //ob³uga clipboarda; kopiowanie
			{
				SDL_SetClipboardText(ip.c_str());
			}
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) //wklejanie
			{
				ip = SDL_GetClipboardText();
				renderText = true;
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					//Append character
					ip += e.text.text;
					renderText = true;
				}
			}
		}

		if (renderText)
		{
			//Text is not empty
			if (ip != "")
			{
				//Render new text
				parentWindow->clear();
				parentWindow->printTextOnScreenCenteredHorizontally(ip, 200, 150, WHITE);
				inputMenu->staticRender();
			}
			//Text is empty
			else
			{
				//Render space texture
				parentWindow->clear();
				parentWindow->printTextOnScreenCenteredHorizontally(" ", 200, 150, WHITE);
				inputMenu->staticRender();
			}
		}
		parentWindow->update();

	}
	return false;
}



//--------------------SCREEN SCOREBOARD--------------------

ScreenScoreBoard::ScreenScoreBoard(Window *win)
{
	parentWindow = win;
}

void ScreenScoreBoard::render(Board *board, int playerNum)
{
	parentWindow->printTextOnScreenCenteredHorizontally("Scoreboard:", y, 100, WHITE);

	int tablePos = y + 30, yTemp;
	std::string text = "";

	for (int i = 1; i < PLAYERS_NUMBER + 1; i++)
	{
		yTemp = tablePos + i * 70;
		if (i == playerNum)
			text = std::string("YOU: ")+ std::to_string(board->score[i - 1]);
		else
			text = std::string("PLAYER_") + std::to_string(i) + std::string(": ") + std::to_string(board->score[i - 1]);
		parentWindow->printTextOnScreenCenteredHorizontally(text, yTemp, 150, PLAYER_COLORS[i - 1]);
		
	}

	parentWindow->printTextOnScreenCenteredHorizontally("Press any key to get back to menu...", parentWindow->getHeight()-100, 60, WHITE);
}



//--------------------SCREEN OPTIONS MENU--------------------

ScreenOptionsMenu::ScreenOptionsMenu(Window *win)
{
	parentWindow = win;

	menuList = { "Toggle fullscreen", "Back" };
	////MENU TEST
	this->optionsMenu = new Menu(parentWindow, menuList, { 100, 100, 100, 255 }, { 255, 255, 255, 255 }, 150, 10);

}



bool ScreenOptionsMenu::startMenu(SDL_Event &e)
{
	//inicjalizacja zmiennych, resetowanie menu
	bool exit = false;
	//int position;
	std::string position = "";
	optionsMenu->resetMenu();

	//wyswietlenie menu 
	parentWindow->clear();
	position = optionsMenu->staticRender();
	parentWindow->update();

	//petla g³owna
	while (true)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT)
			{
				return true;
			}
			else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
			{
				switch (e.key.keysym.sym)
				{//obs³uga strza³kami
				case SDLK_UP:
					parentWindow->clear();
					position = optionsMenu->moveUp();
					break;
				case SDLK_DOWN:
					parentWindow->clear();
					position = optionsMenu->moveDown();
					break;
				case SDLK_RETURN:
					if (position.compare(menuList.at(0)) == 0)
					{
						
						//zmien napis w menu
						//optionsMenu->
						if (parentWindow->isFullscreen)
							menuList = { "Toggle fullscreen", "Back" };
						else
							menuList = { "Turn off fullscreen", "Back" };
						parentWindow->switchFullscreen();
						this->optionsMenu->changeFields(menuList);
						parentWindow->clear();
						parentWindow->update();
						position = optionsMenu->staticRender();
						////MENU TEST
						
					}
					else if (position.compare(menuList.at(1)) == 0)
					{
						//wroc do main menu
						return false;
					}

					break;
				default:
					break;

				}
			}
		}
		parentWindow->update();



	}
	return false;
}