#include "communication.h"


communication::communication(const char* ip, int port) //
{
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		printf("Initialization error.\n");
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		printf("Error creating socket: %ld\n", WSAGetLastError());
		WSACleanup();
	}

	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(port);
}

communication::communication(SOCKET mainSocketIn)
{
	this->mainSocket = mainSocketIn;
}

bool communication::conect()
{
	if (connect(mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("Failed to connect.\n");
		WSACleanup();
		return false;
	}
	return true;
}

void communication::sendDirection(int toSend)
{
	send(mainSocket, (char *)&toSend, sizeof(int), 0);
}

void communication::sendRecevData(recevData toSend)
{
	send(mainSocket, (char *)&toSend, sizeof(recevData), 0);
}

int communication::receiveDirection()
{
	char recbuf[sizeof(direction)];
	direction tmp;
	recv(mainSocket, recbuf, sizeof(direction), 0);
	memcpy(&tmp, recbuf, sizeof(direction));
	return tmp;
}

recevData communication::receiveRecevData()
{
	char recbuf[sizeof(recevData)];
	recevData tmp;
	recv(mainSocket, recbuf, sizeof(recevData), 0);
	memcpy(&tmp, recbuf, sizeof(recevData));
	return tmp;
}


server::server(char* ip, int port, int numberOfPleyersIn)
{
	this->numberOfPlayers = numberOfPleyersIn;

	data = new dataToThread[numberOfPleyersIn];
	thread = new HANDLE[numberOfPleyersIn];
	/*³adowanie bibliotek*/
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		printf("Blad ladowania biblioteki.\n");
	else
		printf("Zaladowano biblioteke. \n");

	/*startowanie socketu*/
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		printf("Socket nie wystartowal bo: %ld\n", WSAGetLastError());
		WSACleanup();
	}
	else
	{
		printf("Socket wystartowal. \n");
	}

	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(port);
}

void server::listen_bind()
{
	/*zbindowanie serwera*/
	if (bind(mainSocket, (SOCKADDR *)& service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("Blad bindowania. \n");
		closesocket(mainSocket);
	}
	else
	{
		printf("Bindowanie zakonczone. \n");
	}

	/*start s³uchania*/
	if (listen(mainSocket, 1) == SOCKET_ERROR)
		printf("Blad nasluchiwania.\n");
	else
		printf("Zaczeto nasluchiwanie. \n");
}
void server::acceptPleyers()
{
	
	DWORD id;
	SOCKET tmpSocket = SOCKET_ERROR;
	printf("Czekanie na graczy...\n");

	for (int i = 0; i < numberOfPlayers; i++)
	{
		
		data[i].mySocket = accept(mainSocket, NULL, NULL);
		printf("Podlacznony gracz nr %i\n",i+1);
		data[i].disconect = false;
		data[i].numberOfPlayer = i;
		thread[i] = CreateThread(
			NULL, // atrybuty bezpieczeñstwa
			0, // inicjalna wielkoœæ stosu
			run, // funkcja w¹tku
			(void *)&data[i],// dane dla funkcji w¹tku
			0, // flagi utworzenia
			&id);
		if (thread[i] != INVALID_HANDLE_VALUE)
		{
			SetThreadPriority(thread[i], THREAD_PRIORITY_HIGHEST);
		}
		
	}
	printf("zakonczono przyjmowania graczyt \n");
	
	
}

dataToThread* server::getData()
{
	return data;
}

/*w¹tek obs³uguj¹cy komunikacje z graczem*/
DWORD WINAPI run(void *argumenty)
{
	struct dataToThread *data = (struct dataToThread *)argumenty;
	communication conect(data->mySocket);

		
	int tmp;
	recevData toSend;
	int PlayerNr = data->numberOfPlayer+1;
	data->toSend.Player_nr = PlayerNr;
	printf("wystartowano watek gracza \n");
	printf("start petli\n");

	while (*(data->endRund)==false)
	{
		if (DEBUG==1)
			printf("czekam na dane %d \n", PlayerNr);
		tmp = conect.receiveDirection();
		if (DEBUG == 1)
			printf("dostano dane %d\n", PlayerNr);
		EnterCriticalSection(data->CriticalSection);
		data->move[data->numberOfPlayer]++;
		data->direction = tmp;
		if (tmp <= SOCKET_ERROR)
		{
		/*Jeœli nast¹pi³o przerwanie po³aczaenia*/			
			data->disconect = true;
			LeaveCriticalSection(data->CriticalSection);
			return 0;
		}
		else
		{
			if (data->direction != direction::start)
			{
				if (data->direction != direction::wait)
				{
					data->toSend.end = data->board->setD(data->numberOfPlayer + 1, data->direction);
				}
				int tmp;
				if (data->board->allEnd(&tmp))
					data->toSend.end = ALL_END;
				
				if (DEBUG == 1)
					printf("normalnie  %d\n",PlayerNr);

				data->board->copyField(data->toSend.field);
				data->board->copyScores(data->toSend.score);
				conect.sendRecevData(data->toSend);
			}
			else
			{
				if (DEBUG == 1)
					printf("przed sekcja start \n");
				EnterCriticalSection(data->CriticalStart);
				if (DEBUG == 1)
					printf("przed start \n");
				data->start[data->numberOfPlayer] = true;
				LeaveCriticalSection(data->CriticalSection);
				while (*(data->allStart) == false)
				{
					LeaveCriticalSection(data->CriticalStart);					
					Sleep(1);
					EnterCriticalSection(data->CriticalStart);
				}
				LeaveCriticalSection(data->CriticalStart);
				EnterCriticalSection(data->CriticalSection);
				/*jak startuj*/
				if (*(data->endRund)==false)
				{
					printf("start %d \n", data->numberOfPlayer);
					data->toSend.end = 1;

					switch (data->numberOfPlayer)
					{
					case 0:
						data->board->set(0, 0, data->numberOfPlayer + 1);
						data->direction = direction::right;
						break;
					case 1:
						data->board->set(M - 1, 0, data->numberOfPlayer + 1);
						data->direction = direction::left;
						break;
					case 2:
						data->board->set(M - 1, N - 1, data->numberOfPlayer + 1);
						data->direction = direction::left;
						break;
					case 3:
						data->board->set(0, N - 1, data->numberOfPlayer + 1);
						data->direction = direction::right;
						break;

					default:
						//jakiœ kod
						break;
					}

					data->start[data->numberOfPlayer] = false;
					data->board->copyField(data->toSend.field);
					data->board->copyScores(data->toSend.score);
					conect.sendRecevData(data->toSend);
					conect.sendDirection(data->direction);
					if (DEBUG == 1)
						printf("wyslano start %d \n", PlayerNr);
				}
				else//jak zakoñczy³y siê rundy wys³anie info o tym
				{
					data->toSend.end = ALL_RUND_END;
					conect.sendRecevData(data->toSend);
					conect.sendDirection(data->direction);
				}
			}
			for (int i = 0; i < data->numberOfPlayers; i++)
			{
				while (data->move[data->numberOfPlayer]>data->move[i] + 5)
				{
					LeaveCriticalSection(data->CriticalSection);
					Sleep(1);
					EnterCriticalSection(data->CriticalSection);
				}
			}
			LeaveCriticalSection(data->CriticalSection);
			
		}
	}
}

