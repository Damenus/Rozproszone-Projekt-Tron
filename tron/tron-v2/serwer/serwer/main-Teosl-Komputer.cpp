#include <cstdio>
#include <cstdlib>
#include "D:\Users\OneDrive\Dokumenty\ETI\rozp\projekt\klient\klient\communication.h"
#include <iostream>

using namespace std;

int main()
{
	dataToThread *data;
	int pleyers = 2;
	server main("127.0.0.1", 27015, pleyers);
	Board board;
	data = main.getData();
	main.acceptPleyers();

	bool all = true;

	while (1)
	{
		all = true;
		for (int p= 0; p < pleyers; p++)
		{
			if (data[p].next == false)
			{
				all = false;
			}
		}
		if (all == true)
		{
			for (int i = 0; i<M; i++)
			{
				for (int j = 0; j<N; j++)
				{
					for (int p = 0; p < pleyers; p++)
					{
						if (data[p].board.get(i, j)==2)
							board.set(i, j, p+1);
					}
					cout << board.get(j, i) << " ";
				}
				cout << endl;
			}
			for (int p = 0; p < pleyers; p++)
			{
				data[p].board = board;
				data[p].send = true;
				data[p].next = false;
			}
		}
		
	}
	system("pause");


}