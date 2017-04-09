#ifndef Board_h
#define Board_h

#include"Defines.h"

class Board {
private:

	unsigned const int width = M;
	unsigned const int height = N;
	bool isDead[4];
	struct Point
	{
		int x;
		int y;
	}previous[4];

public:
	int numberOfPlayers=1;
	int score[4];
	Board();
	int get(int x, int y);
	bool set(int x, int y, int player);
	int setD(int player, int direction);
	void clear();
	void clearAll();

	//TABLICA JEST TU
	char field[N][M]; //moglaby sie nazywac w sumie board, ale co wazniejsze
	int ** getField();// to chyba lepiej ja alokowac w konstruktorze
	//bo inaczej chyab sie nie da jej getowaæ wyskakuje, ¿e typy nie pasuja
	//chyba, ze sie myle
	void setField(char in[N][M]);
	void setScore(int player, int hPlayer);

	void setAllScores(short in[4]);

	void copyScores(short out[4]);

	void Board::copyField(char out[N][M]);

	bool allEnd(int *alive);

	unsigned int getWidth();
	unsigned int getHeight();

	int getLast(); //zwraca ostatniego gracza
};



#endif 
