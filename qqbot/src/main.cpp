// 注意: 本项目的所有源文件都必须是 UTF-8 编码

// 这是一个“反撤回”机器人
// 在群里回复 “/anti-recall enabled.” 或者 “撤回没用” 之后
// 如果有人在群里撤回，那么机器人会把撤回的内容再发出来

#include <iostream>
#include <map>
#include <mirai.h>
#include "myheader.h"
using namespace std;
using namespace Cyan;

int main(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot;
	SessionOptions opts = SessionOptions::FromJsonFile("cfg/config.json");

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

/***         Edit my bot here         ***/

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
			
			srvlist = srvlist + "\n==============\n";
			srvlist = srvlist + "Powered by 达达\nGitHub: https://github.com/luckyweNda";
			gm.Reply(MessageChain().Plain(srvlist));
		}

		try
		{
			int lineNum = std::stoi(gm.MessageChain.GetPlainTextFirst());

			if(lineNum > 15)
			{
				return;
			}

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
				a2s_player *players = ssq_player(querier, &player_count);

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

/***         Edit my bot here         ***/       

	bot.On<LostConnection>([&](LostConnection e)
		{
			cout << e.ErrorMessage << " (" << e.Code << ")" << endl;
			while (true)
			{
				try
				{
					cout << "尝试连接 mirai-api-http..." << endl;
					bot.Reconnect();
					cout << "与 mirai-api-http 重新建立连接!" << endl;
					break;
				}
				catch (const std::exception& ex)
				{
					cout << ex.what() << endl;
				}
				MiraiBot::SleepSeconds(1);
			}
		});

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			bot.Disconnect();
			break;
		}
	}

	return 0;
}