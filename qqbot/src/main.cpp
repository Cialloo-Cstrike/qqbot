#include <iostream>
#include <map>
#include <mirai.h>
#include "myheader.h"
using namespace std;
using namespace Cyan;

#define SERVER_PORT 51000
#define SERVER_IP "127.0.0.1"

int g_sockfd = -1;

int main()
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot;
	SessionOptions opts;
	opts.BotQQ = 3199329079_qq;				// 请修改为你的机器人QQ
	opts.HttpHostname = "localhost";		// 请修改为和 mirai-api-http 配置文件一致
	opts.WebSocketHostname = "localhost";	// 同上
	opts.HttpPort = 8084;					// 同上
	opts.WebSocketPort = 8084;				// 同上
	opts.VerifyKey = "qtocss";			// 同上

	CreateClientSocket();

	while (true)
	{
		try
		{
			cout << "尝试与 mirai-api-http 建立连接..." << endl;
			bot.Connect(opts);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

	/***      Edit my bot here.      ***/

	bot.On<FriendMessage>(
		[&](FriendMessage fm)
		{
			fm.Reply(MessageChain().Plain("This is a bot test."));	// It works.
		}
		);

	bot.On<GroupMessage>(
		[&](GroupMessage gm)
		{

		}
	);


	/***           my bot            ***/

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			// 程序结束前必须调用 Disconnect，否则 mirai-api-http 会内存泄漏。
			bot.Disconnect();
			break;
		}
	}

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