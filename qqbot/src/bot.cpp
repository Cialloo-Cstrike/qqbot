#include <iostream>
#include <map>
#include <mirai.h>
#include "myheader.h"
using namespace Cyan;

extern MiraiBot bot;


void MainBot()
{
	bot.On<GroupMessage>([&](GroupMessage gm)
	{
		if(gm.MessageChain.GetPlainTextFirst() == "server" 
		|| gm.MessageChain.GetPlainTextFirst() == "服务器")
		{
			char filepath[64];
			sprintf(filepath, "./cfg/srv_intro/%ld.txt", gm.Sender.Group.GID.ToInt64());

			std::ifstream file;
			file.open(filepath);

			if(!file.is_open())
			{
				printf("Cannot open file %s.\n", filepath);
				return;
			}

			std::string line, srvlist;
			
			while(std::getline(file, line))
			{
				srvlist = srvlist + line + '\n';
			}

			file.close();
			
			srvlist = srvlist + "\n==============\n";
			srvlist = srvlist + "Powered by 达达\nGitHub: https://github.com/luckyweNda";
			gm.Reply(MessageChain().Plain(srvlist));
		}

		try
		{
			if(gm.MessageChain.GetPlainTextFirst().length() > 1)
			{
				return;
			}

			int lineNum = std::stoi(gm.MessageChain.GetPlainTextFirst());

			char filepath[64];
			sprintf(filepath, "./cfg/srv_ip/%ld.txt", gm.Sender.Group.GID.ToInt64());

			std::ifstream file;
			file.open(filepath);

			if(!file.is_open())
			{
				std::cout << "Cannot find group: " << gm.Sender.Group.GID.ToInt64() << std::endl;
				return;
			}

			int num = 0;
			std::string srvip;

			while(num != lineNum && std::getline(file, srvip))
			{
				num++;
			}

			file.close();

			if(num == lineNum)
			{
				std::stringstream line(srvip);
				std::string ip, port, output;

				std::getline(line, ip, ':');
				std::getline(line, port);

				ssq_querier *querier = ssq_init();
				ssq_set_timeout(querier, SSQ_TIMEOUT_RECV, 3000);
				ssq_set_timeout(querier, SSQ_TIMEOUT_SEND, 3000);

				ssq_set_target(querier, ip.c_str(), (uint16_t)std::stoi(port));

				uint8_t player_count = 0;
				a2s_info *info = ssq_info(querier);

				if (!ssq_ok(querier)) 
				{
					const char *error_message = ssq_errm(querier);
					fprintf(stderr, "ssq_info: %s\n", error_message);

					ssq_errclr(querier);

					return;
				}

				a2s_player *players = ssq_player(querier, &player_count);

				if (!ssq_ok(querier)) 
				{
					const char *error_message = ssq_errm(querier);
					fprintf(stderr, "ssq_info: %s\n", error_message);

					ssq_errclr(querier);

					return;
				}

				output = output + info->name + '\n' 
				+ "地图: " + info->map + '\n'
				+ "玩家人数: " + std::to_string(info->players) + '\n'
				+ "玩家列表\n" + "==============\n";

				for (uint8_t index = 0; index < player_count; index++)
				{
					output = output + players[index].name + '\n';
				}

				output = output + "==============";
				gm.Reply(MessageChain().Plain(output));
			}
		}
		catch(std::exception &e)
		{
			std::cout << "Catch an error: " << e.what() << std::endl; 
		}
	});

	// relay server
	pthread_t socket_thread;
	pthread_create(&socket_thread, NULL, RelayServer, NULL);
}