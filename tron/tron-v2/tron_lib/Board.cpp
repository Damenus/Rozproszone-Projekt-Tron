#include "Board.h"
#include <stdio.h>

Board::Board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			field[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		isDead[i] = false;
		score[i] = 0;
	}
	previous[0].x = 0;
	previous[0].y = 0;
	previous[1].x = M - 1;
	previous[1].y = 0;
	previous[2].x = M - 1;
	previous[2].y = N - 1;
	previous[3].x = 0;
	previous[3].y = N - 1;
}
int Board::get(int x, int y)// x - wspó³rzêdna w poziomie, y - wspó³rzêdna w pionie 
{
	if (x >= 0 && x < M && y >= 0 && y < N)
	{
		return field[y][x];
	}
	return -1;
}
bool Board::set(int x, int y, int player)
{
	if (player > 0 && player < 5 && field[y][x] == 0 && x< M && y<N && x > -1)
	{
		field[y][x] = player;
		return true;
	}
	else
		return false;
}

//ustawienie gracza na nowej pozycji;
//1 - uda³o siê zrobiæ ruch
//@ - gracz wpad³ na gracza 1, #  - gracz wpad³ na gracza 2 itd...
//0 - gracz poza plansz¹
int Board::setD(int player, int directionIn)
{
	
	//printf("%d - %d \n", previous[player - 1].x, previous[player - 1].y);
	if (player > 0 && player < 5 && (previous[player - 1].x < M-1 || (previous[player - 1].x == M-1 && directionIn != direction::right)) && (previous[player - 1].y < N-1 || (previous[player - 1].y == N-1 && directionIn != direction::down)) && (previous[player - 1].x > 0 || (previous[player - 1].x == 0 && directionIn != direction::left)) && (previous[player - 1].y > 0 || (previous[player - 1].y == 0 && directionIn != direction::up)))//trzeba dopisaæ wiêcej warunklów typu ||
	{
		int x, y;
		x = previous[player - 1].x;
		y = previous[player - 1].y;
		switch (directionIn)
		{
		case direction::down:
			y += 1;
			break;

		case direction::up:
			y -= 1;
			break;

		case direction::left:
			x -= 1;
			break;

		case direction::right:
			x += 1;
			break;
		}
		if (field[y][x] == 0)//brak kolizji, wykonanie ruchu
		{
			if (player == 1)
			{
				field[y][x] = '@';
			}
			else if (player == 2)
			{
				field[y][x] = '#';
			}
			else if (player == 3)
			{
				field[y][x] = '$';
			}
			else
			{
				field[y][x] = '%';
			}
			field[previous[player - 1].y][previous[player - 1].x] = player;
			previous[player - 1].x = x;
			previous[player - 1].y = y;
			return 1;
		}
		else//sprawdzenie z kim nast¹pi³a kolizja
		{
			int toReturn;
			if (field[y][x] == 1 || field[y][x] == '@')
			{
				setScore(player, 1);
				toReturn = '@';
			}
			else if (field[y][x] == 2 || field[y][x] == '#')
			{
				setScore(player, 2);
				toReturn = '#';
			}
			else if (field[y][x] == 3 || field[y][x] == '$')
			{
				setScore(player, 3);
				toReturn = '$';
			}
			else if (field[y][x] == 4 || field[y][x] == '%')
			{
				setScore(player, 4);
				toReturn = '%';
			}
			int tmp;
			this->allEnd(&tmp);
			if (tmp == 1)
				isDead[this->getLast()] = true;

			return toReturn;
		}
	}
	else//gracz poza plansz¹
	{
		isDead[player - 1] = true;
		int tmp;
		this->allEnd(&tmp);
		if (tmp == 1)
			isDead[this->getLast()] = true;
		return 0;
	}	
}
void Board::clear()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			field[i][j] = 0;
		}
	}
	previous[0].x = 0;
	previous[0].y = 0;
	previous[1].x = M - 1;
	previous[1].y = 0;
	previous[2].x = M - 1;
	previous[2].y = N - 1;
	previous[3].x = 0;
	previous[3].y = N - 1;
	for (int i = 0; i < 4; i++)
	{
		isDead[i] = false;
	}
}

void Board::clearAll()
{
	this->clear();

	for (int i = 0; i < 4; i++)
	{
		isDead[i] = false;
		score[i] = 0;
	}
}

//int** Board::getField()
//{
//	return *field[];
//}


unsigned int Board::getWidth()
{
	return width;
}

unsigned int Board::getHeight()
{
	return height;
}

void Board::copyField(char out[N][M])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			out[i][j] = field[i][j];
}

void Board::copyScores(short out[4])
{
	for (int i = 0; i < 4; i++)
		out[i] = score[i];
}

void Board::setField(char in[N][M])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			field[i][j] = in[i][j];
}

void Board::setAllScores(short in[4])
{
	for (int i = 0; i < 4; i++)
		score[i] = in[i];
}

void Board::setScore(int player, int hPlayer)
{
	isDead[player - 1] = true;
	int numberOfDead=0;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (!isDead[i])
			score[i] += 20;//ka¿dy gracz, który nie jest martwy dostaje punkty
	}

	if (hPlayer != 0 && player != hPlayer)
		score[hPlayer - 1] += 30;//gracz, w którego œlad wjechano dostaje punkty	
}

bool Board::allEnd(int *alive)//metoda zwraca true jak wszyscy umarli, argument alive zwraca liczbe ¿ywych graczy
{
	*alive = 0;
	bool tmp = true;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (isDead[i] == false)
		{
			*alive+=1;
			tmp = false;
		}
	}
	return tmp;
}

int Board::getLast()
{
	int tmp;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (isDead[i] == false)
		{
			tmp = i;
			break;
		}
	}
	return tmp;
}