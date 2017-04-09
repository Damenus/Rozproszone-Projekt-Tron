
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <cstdio>
#include <winsock2.h>
#include <cstdlib>
#include <Board.h>


#pragma comment(lib, "Ws2_32.lib")

DWORD WINAPI run(void *argumenty);


struct recevData //dane wysy³ane z serwera do gracza
{
	char field[N][M];
	short int score[4];
	int end = 0;
	int Player_nr;
};

struct dataToThread //dane do w¹tku
{
	SOCKET mySocket;
	recevData toSend;
	int direction;
	int numberOfPlayer;
	int numberOfPlayers;
	int *move; //tablica z informacja który ruch
	bool *start;
	CRITICAL_SECTION *CriticalSection;
	CRITICAL_SECTION *CriticalStart;
	Board *board;
	bool disconect;
	bool *allStart;
	bool *endRund;
};


class communication{
private:
	WSADATA wsaData;
	SOCKET mainSocket;
	sockaddr_in service;

public:
	communication(const char* ip, int port);
	communication(SOCKET mainSocket);

	void sendRecevData(recevData toSend);
	void sendDirection(int toSend);
	int receiveDirection();
	recevData receiveRecevData();
	bool conect();

};

class server{
private:
	WSADATA wsaData;
	SOCKET mainSocket;
	dataToThread *data;
	sockaddr_in service;
	int numberOfPlayers;
	HANDLE *thread;
	CRITICAL_SECTION *CriticalSection;
	Board *board;

public:
	server(char* ip, int port, int numberOfPleyersIn);
	void listen_bind();
	void acceptPleyers();
	dataToThread* getData();

};