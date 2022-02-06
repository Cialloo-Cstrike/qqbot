#include "qqbot.hpp"

#define SERVER_PORT 51000
#define SERVER_IP "127.0.0.1"

int g_sockfd = -1;

bool QQBot::Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
	ConnectTier1Libraries( &interfaceFactory, 1 );
	ConnectTier2Libraries( &interfaceFactory, 1 );

	CreateClientSocket();

	MathLib_Init( 2.2f, 2.2f, 0.0f, 2.0f );
	ConVar_Register( 0 );

    return true;
}

void QQBot::Unload( void )
{
	close(g_sockfd);
}

void QQBot::LevelInit( char const *pMapName )
{
	pthread_t sendmsg;
	pthread_create(&sendmsg, NULL, SendMapInfo, NULL);
}

void* SendMapInfo(void* args)
{
	
	return 0;
}

void CreateClientSocket()
{
	g_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(g_sockfd == -1)
	{
		printf("Create socket error.\n");
		return;
	}

	sockaddr_in  servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

	int check = -1;
	check = inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);

	if(check == -1)
	{
		printf("inet_pton error.\n");
		return;
	}

	int cn = -1;
	cn = connect(g_sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	if(cn == -1)
	{
		printf("Socket connect fail.\n");
		return;
	}

	printf("\nIt's time to send msg to server. \n");
}