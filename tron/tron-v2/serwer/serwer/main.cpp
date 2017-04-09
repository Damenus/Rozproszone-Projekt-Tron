#include <cstdio>
#include <cstdlib>
#include "communication.h"
#include <iostream>


CRITICAL_SECTION CriticalSection, CriticalStart;


using namespace std;

int main()
{

	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
		0x00000400))
		return 0;
	if (!InitializeCriticalSectionAndSpinCount(&CriticalStart,
		0x00000400))
		return 0;

	bool allStart = true;
	char adress[25];
	int pleyers = 2;
	int move[4];
	bool start[4];
	int rund = 1;
	bool endRund = false;
	printf("Podaj adress ip \n");
	cin >> adress;

	printf("Podaj liczbe graczy \n");
	scanf_s("%d", &pleyers);

	dataToThread *data;
	Board MainBoard;
	MainBoard.numberOfPlayers = pleyers;
	server main(adress, 27025, pleyers);
	
	recevData toSend;
	data = main.getData();

	for (int i = 0; i < 4; i++)
	{
		move[i] = 0;
		start[i] = false;		
	}
	for (int i = 0; i < pleyers; i++)
	{
		data[i].endRund = &endRund;
		data[i].allStart = &allStart;
		data[i].move = move;
		data[i].start = start;
		data[i].CriticalSection = &CriticalSection;
		data[i].CriticalStart = &CriticalStart;
		data[i].board = &MainBoard;
		data[i].numberOfPlayers = pleyers;
	}
	
	main.listen_bind();
	MainBoard.clearAll();
	EnterCriticalSection(&CriticalSection);
	main.acceptPleyers();
	LeaveCriticalSection(&CriticalSection);


	
	while (endRund==false)
	{	
		EnterCriticalSection(&CriticalStart);
		allStart = true;
		for (int i = 0; i < pleyers; i++)
		{
			if (start[i] == false)
				allStart = false;
		}
		if (allStart == true)
		{
			printf("runda %d \n", rund);
			MainBoard.clear();
			if (rund > RUNDS)
				endRund = true;
			rund++;
		}
		LeaveCriticalSection(&CriticalStart);
		Sleep(500);
	}
	Sleep(10000);
	DeleteCriticalSection(&CriticalSection);
	DeleteCriticalSection(&CriticalStart);
	system("pause");

}