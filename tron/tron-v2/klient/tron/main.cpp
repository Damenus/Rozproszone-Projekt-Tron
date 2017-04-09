/*
1. zalaczaenie SDL'a: https://www.youtube.com/watch?v=I-yOf4Xg_R8
-on wrzuca dll-ke do debuga, a powino sie tam gdzie main
-sdl image załączamy analogicznie, wrzucamy folder, ustawiamy miejsce includow, libow, tak gdzie sdl2.lib itp wpisywal
wpisujemy sdl_im...lib *(to z folderu x86), i po buildzie kopiujemy wszystkie dll to folderu z mainem
2. http://lazyfoo.net/tutorials/SDL/

*/
#define _CRT_SECURE_NO_WARNINGS
#include "communication.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>


#include "Defines.h"
#include "Texture.h"
#include "Player.h"
#include "Board.h"
#include "Timer.h"
#include "Screens.h"
#include "Window.h"
#include "Font.h"
#include "Menu.h"
#include "DefinesSDL.h"

//który ekran
enum gamemode gamemode;

std::string inputText;

bool init();		//inicjalizacja - sdl,okno itp
bool loadFiles();	//wczytanie plikow - tekstury itp
bool createObjects();
void close();		//zwolnienie powierzchni, pamieci itp.

std::string ip;


Window *window;
Player *player = new Player(1, 0, 0);	//gracz

//ekrany w strukturach - patzr screens_h
ScreenGame *screenGame;
ScreenMainMenu *screenMainMenu;
ScreenInputIpMenu * screenInputIpMenu;
ScreenScoreBoard * screenScoreBoard;
ScreenOptionsMenu * screenOptionsMenu;
Font *tronFont = new Font();

communication *connection;


//timer do fpsow
Timer fpsTimer;

//timer do blokowania ilosci fpsow
Timer capTimer;

double coun = 0.0;
int direction = 1; //prawo - 1, góra - 2, lewo - 3, dół - 4 

bool observe = false; //flaga odpowiedzialna za to czy zczytujemy ruchy gracza

int main(int argc, char* args[])
{
	
	
	//tutaj zapisuje wszelkie printfy itp - do sprawdzania bledow
	FILE * crashlog = freopen("crashlog.txt", "wb", stdout);
	Board *board = new Board();	//obiekt planszy
	gamemode = mainmenu;
	int myDirection;


	if (!init())
	{
		printf("Problem w inicjalizacji\n");
	}
	else
	{
		if (!loadFiles())
		{
			printf("Problem z wczytaniem plikow\n");
		}
		else
		{
			if (!createObjects())
			{
				printf("Problem z utworzeniem obiektów\n");
			}
			else
			{
				bool quit = false;
				SDL_Event e;	//do obslugi eventow

				//connect.conect();//podłaczenie do serwera
				int myDirection=right;//zmiena przechowywująca ruch gracza
				recevData receve;//dane otrzymywane od serwera



				int countedFrames = 0;
				fpsTimer.start();

				//PETLA GLOWNA
				while (!quit)
				{
					capTimer.start();

					float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);

					if (avgFPS > 2000000)
					{
						avgFPS = 0;
					}
					
					
					if (gamemode == game)
					{
						while (SDL_PollEvent(&e) != 0)
						{

							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
							{
								if (observe == false)
								{
									switch (e.key.keysym.sym)
									{
									case SDLK_UP:
										if (player->getDirection() != down)
										{
											myDirection = up;
										}
										break;

									case SDLK_DOWN:
										if (player->getDirection() != up)
										{
											myDirection = down;
										}
										break;

									case SDLK_LEFT:
										if (player->getDirection() != right)
										{
											myDirection = left;
										}
										break;

									case SDLK_RIGHT:
										if (player->getDirection() != left)
										{
											myDirection = right;
										}
										break;

									case SDLK_ESCAPE:	//zakonczenie
										quit = true;
										break;
									default:
										break;

									}
								}
							}
						}
						player->setDirection(myDirection);//ustawienie kierunku gracza


						/*wysłanie i odbiór danych na serwer*/
						Sleep(1);
						connection->sendDirection(myDirection);
						receve = connection->receiveRecevData();

						if (receve.end == 1|| (observe==true && receve.end!=ALL_END))//jeśli nie nastąpiła kolizja
						{
							board->setField(receve.field);
							board->setAllScores(receve.score);
							
							//Czyszczenie ekranu
							window->clear();							
							//renderowanie graczy i sladow
							screenGame->render(board, receve.Player_nr);
							//rysowanie fpsów
							//window->printTextOnScreen(, 0, 0, 50, WHITE);

							window->renderPlayers(board);


							//Update screen
							window->update();
						}
						else
						{
							if (receve.end == ALL_END) //jezeli runda sie skonczyla, to przejdz do ekranu oczekiwaia na kolejna
							{
								gamemode = nextround;
							}
							//else if (receve.end == ALL_RUND_END)	//jezeli to koniec wszystkich rund, przejdz do scoreboarda
							//{
							//	gamemode = scoreboard;
							//}
							else    //jezeli gra trwa dalej, zmien sie w obserwatora
							{
								observe = true;
								myDirection = wait;
							}
						}
					}
					else if (gamemode == nextround)
					{


						//rendering
						window->clear();
						window->printTextOnScreenCentered("Waiting for next round", 150, WHITE);
						window->printTextOnScreenCenteredHorizontally("Press any key if you ready.", window->getHeight() / 2 + 50, 60, WHITE);
						window->update();

						while (SDL_PollEvent(&e) != 0)
						{

							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							else if (e.type == SDL_KEYDOWN) //jak zostanei wcisniety klawisz
							{
								//zmien wyswietlanie na ready
								window->clear();
								window->printTextOnScreenCentered("Waiting for next round", 150, WHITE);
								window->printTextOnScreenCenteredHorizontally("READY", window->getHeight() / 2 + 50, 200, WHITE);
								window->update();
								
								//wyczysc plansze i zacznij polaczenie
								board->clear();
								player->reset();
								connection->sendDirection(start);
								/*odebranie początkowej planszy i kierunku gracza*/
								receve = connection->receiveRecevData();
								if (receve.end == ALL_RUND_END)
								{
									gamemode = scoreboard;
									continue;
								}
								board->setField(receve.field);
								myDirection = connection->receiveDirection();
								observe = false;
								gamemode = game;
							}
						}
					
					}
					else if (gamemode == mainmenu)
					{
						if (screenMainMenu->startMenu(gamemode, e))
						{
							quit = true;
						}

					}
					else if (gamemode == optionsmenu)
					{
						if (screenOptionsMenu->startMenu(e))
						{
							quit = true;
						}

						gamemode = mainmenu;

					}
					else if (gamemode == inputipmenu)
					{
						//odpalenie menu z inputem - w środu od razu weryfikacja ip
						if (screenInputIpMenu->startMenu(e, ip))
						{
							//jezeli wyszlo z menu
							gamemode = mainmenu;
							continue;
						}
						//jak nie, to znaczy ze dobre ip wpisano, przechodzimy do łączenia z serwerem
						
						gamemode = waitforconnection;
						
						

					}
					else if (gamemode == waitforconnection)
					{

						connection = new communication(ip.c_str(), 27025);//stworzenie obiektu odpowiedzialnego za komunikacje

						//wyrenderuj czekanie
						window->clear();
						window->printTextOnScreenCentered("Connecting...", 150, WHITE);
						window->update();

						if (connection->conect())//podłączenie do serwera
						{
							board->clear();
							player->reset();
							connection->sendDirection(start);
							/*odebranie początkowej planszy i kierunku gracza*/
							receve = connection->receiveRecevData();
							board->setField(receve.field);
							myDirection = connection->receiveDirection();
							gamemode = game;
							ip = "";
						}
						else
						{
							//nie udała sie komunikacja
							gamemode = failedConnection;
							ip = "";
						}


					}
					else if (gamemode == failedConnection)
					{

					
						window->clear();
						window->printTextOnScreenCentered("Failed to connect", 150, WHITE);
						window->printTextOnScreenCenteredHorizontally("Press any key to get back to menu...", window->getHeight() / 2 + 50, 60, WHITE);
						window->update();

						while (SDL_PollEvent(&e) != 0)
						{

							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
							{
								gamemode = mainmenu;
							}
						}

					}
					else if (gamemode == scoreboard)
					{


						window->clear();
						screenScoreBoard->render(board,receve.Player_nr);
						window->update();

						while (SDL_PollEvent(&e) != 0)
						{

							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							else if (e.type == SDL_KEYDOWN) //obsluga klawiatury
							{
								gamemode = mainmenu;
							}
						}

					}

					++countedFrames;

					//If frame finished early
					int frameTicks = capTimer.getTicks();
					if (frameTicks < SCREEN_TICK_PER_FRAME)
					{
						//Wait remaining time
						SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
					}

				}
			}
			}

			
		}

		//Free resources and close SDL
		close();
		fclose(crashlog);	//zampkij plik
		return 0;
}


bool init()
{
	//właczenie sdla
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Blad inicjalizacji SDL: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//?
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("problem z sdl_setHint");
		}

		try
		{
			window = new Window("TRON",SCREEN_WIDTH,SCREEN_HEIGHT);

			//mozliwosc wczytywania plikow png
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("Problem z inicjalizacja SDL_Image: %s\n", IMG_GetError());
				return false;
			}
			//init czcionek
			if (TTF_Init() == -1)
			{
				printf("Problem z inicjalizacja SDL_ttf: %s\n", TTF_GetError());
				return false;
			}


		}
		catch (char * ex)
		{
			printf("%s", ex);
			close();
			return false;
		}

				
				
	}
	return true;
}


bool loadFiles()
{
	try{
		
		window->texPack.loadTextures(window->winRenderer);
		tronFont->load("fonts\\tron2.ttf");
		window->fontTron = tronFont;
	}
	catch (std::string ex)
	{
		
		printf("%s", ex);
		close();
		return false;
	}	


	return true;
}

bool createObjects()
{
	try{

		screenGame = new ScreenGame(window);
		screenMainMenu = new ScreenMainMenu(window);
		screenInputIpMenu = new ScreenInputIpMenu(window);
		screenScoreBoard = new ScreenScoreBoard(window);
		screenOptionsMenu = new ScreenOptionsMenu(window);
	}
	catch (char * ex)
	{
		printf("%s", ex);
		close();
		return false;
	}
	return true;
}


void close()
{
	//Free loaded images
	window->texPack.free();

	//Destruktor okna i renderera
	window->destroy();
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

