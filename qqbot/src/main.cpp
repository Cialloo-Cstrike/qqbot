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
		if(gm.MessageChain.GetPlainTextFirst() == "server")
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
				std::string ip, port;

				std::getline(line, ip, ':');
				std::getline(line, port);

				srcon client = srcon(ip, std::stoi(port), argv[1]);
				std::string response = client.send("status");

				std::string output = ModifyResponse(response);
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

std::string ModifyResponse(std::string response)
{
	std::stringstream all(response);
	std::stringstream line;
	std::string output, temp;

	/*   host name   */
	std::getline(all, temp);
	line << temp;
	std::getline(line, temp, ' ');
	std::getline(line, temp);

	output = output + temp + '\n';

	line.str("");
	line.clear();
	// end of host name.

	/*   Map name   */
	for(int i = 0; i < 4; i++)
	{
		std::getline(all, temp);
	}

	line << temp;

	for(int i = 0; i < 7; i++)  // space counts plus 1
	{
		std::getline(line, temp, ' ');
	}

	output = output + "Map: " +temp + '\n';

	line.str("");
	line.clear();
	// end of map name.

	/*   player counts   */
	for(int i = 0; i < 2; i++)
	{
		std::getline(all, temp);
	}

	line << temp;
	std::getline(line, temp, ' ');

	if(temp == "sourcetv")
	{
		line.str("");
		line.clear();
		std::getline(all, temp);

		output = output + temp + '\n';
	}
	else 
	{
		std::getline(line, temp, ' ');
		std::getline(line, temp, ' ');
		output = output + "playerCount: " + temp + '\n';

		line.str("");
		line.clear();
	}
	// end of player count.

	/*   Player list   */
	output = output + "Player list:\n";

	for(int i = 0; i < 2; i++)  // clear 
	{
		std::getline(all, temp);
	}

	while(std::getline(all, temp))
	{
		line << temp;
		std::getline(line, temp, '\"');
		std::getline(line, temp, '\"');

		output = output + temp +'\n';

		line.str("");
		line.clear();
	}

	output = output + "============";

	return output;
}