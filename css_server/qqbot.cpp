#include "qqbot.hpp"

#define SERVER_PORT 51000
#define SERVER_IP "127.0.0.1"

int g_sockfd = -1;

IVEngineServer *g_engine = NULL;

bool QQBot::Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
	ConnectTier1Libraries( &interfaceFactory, 1 );
	ConnectTier2Libraries( &interfaceFactory, 1 );

	g_engine = (IVEngineServer*)interfaceFactory(INTERFACEVERSION_VENGINESERVER, NULL);

	if(!g_engine)
	{
		printf("\nLoad interface failed.\n");
		return false;
	}
	else
	{
		printf("\nLoad interface successful.\n");
	}

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
	char buffer[256];
	sprintf(buffer, "%d%s", CHANGEMAP, g_engine->GetIServer()->GetMapName());

	int check = -1;
	check = send(g_sockfd, buffer, sizeof(buffer), 0);

	if(check == -1)
	{
		printf("Send map info failed.\n");
	}

	return 0;
}

void QQBot::ClientActive( edict_t *pEntity )
{
	pthread_t sendpinfo;
	pthread_create(&sendpinfo, NULL, SendPlayerInfo, (void*)pEntity);
}

void* SendPlayerInfo(void* args)
{
	//pEntity == (edict_t*)args;
	player_info_t info;
	g_engine->GetPlayerInfo(g_engine->IndexOfEdict((edict_t*)args), &info);
	
	char buffer[256];
	sprintf(buffer, "%d", PLAYERCONNECT);

	int check = -1;
	check = send(g_sockfd, buffer, sizeof(buffer), 0);

	if(check == -1)
	{
		printf("Send player connect info failed.\n");
	}
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