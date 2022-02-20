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

void SendRecordToGroup(std::string &message);
void *RelayServer(void* args);

MiraiBot bot;
SessionOptions opts = SessionOptions::FromJsonFile("cfg/config.json");

int main(int argc, char* argv[])
{
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

			file.close();
			
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

	// relay server
	pthread_t socket_thread;
	pthread_create(&socket_thread, NULL, RelayServer, NULL);

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

void *RelayServer(void* args)
{
    int m_sockfd = -1;
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(m_sockfd == -1)
    {
        printf("Create socket error.\n");
        return 0;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(51000);

    int m_bindfd = -1;
    m_bindfd = bind(m_sockfd, (sockaddr*)&server_addr, sizeof(server_addr));

    if(m_bindfd == -1)
    {
        printf("Bind socket error.\n");
        return 0;
    }

    int m_listenfd = -1;
    m_listenfd = listen(m_sockfd, 10);

    if(m_listenfd == -1)
    {
        printf("Listen socket error.\n");
        return 0;
    }

    /***      Starting to build select      ***/   
    fd_set tmpfd;
    int max_fd = m_sockfd;
    std::vector<int> array_fd;
    sockaddr_in client_addr;
    int size = sizeof(client_addr);

    while(true)
    {
        FD_ZERO(&tmpfd);
        FD_SET(m_sockfd, &tmpfd);

        // 所有在线的客户端加入到fd中
        for(auto it = array_fd.begin(); it < array_fd.end(); it++)
        {
            FD_SET(*it, &tmpfd);
        }

        int ret = -1;
        ret = select(max_fd + 1, &tmpfd, NULL, NULL, NULL);

        if(ret == -1)
        {
            printf("select error.\n");
            continue;
        }
        else if(ret == 0)
        {
            printf("Select time out.\n");
            continue;
        }

        //表示有客户端连接
        if(FD_ISSET(m_sockfd, &tmpfd))
        {
            int m_connfd = -1;
            m_connfd = accept(m_sockfd, (struct sockaddr *)&client_addr,(socklen_t*)&size);

            if(m_connfd == -1)
            {
                printf("Accept connection failed.\n");
                continue;
            }

            printf("we got a new connection, client_count=%d, ip=%s, port=%d\n", 
            m_connfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            array_fd.push_back(m_connfd);

            if(m_connfd > max_fd)
            {
                max_fd = m_connfd;
            }
        }

        //遍历所有的客户端连接，找到发送数据的那个客户端描述符
        for(auto it = array_fd.begin(); it < array_fd.end(); it++)
        {
            if (FD_ISSET(*it, &tmpfd))
            {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                int recv_len = -1;
                recv_len = recv(*it, buffer, sizeof(buffer), 0);

                if(recv_len == -1)
                {
                    printf("Receive data error.\n");
                    break;
                }
                else if(recv_len == 0)
                {
                    close(*it);
                    FD_CLR(*it, &tmpfd);
                    array_fd.erase(it);

                    printf("client_socket=[%d] close, ip=%s, port=%d\n\n", 
                    *it, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                }
                else
                {
                    buffer[recv_len] = '\0';
                    printf("server recv:\n%s\n", buffer);

					std::stringstream message(buffer);
					std::string line, output;
					std::getline(message, line);

					switch(std::stoi(line))
					{
						case NULLMSG:
						{
							send(*it, "0", 8, 0);
						}
						case SURFWR:
						{
							while(std::getline(message, line))
							{
								output = output + line + '\n';
							}

							output = output + "Congratulations!";
							SendRecordToGroup(output);
						}
						case SURFFINISH:
						{
							while(std::getline(message, line))
							{
								output = output + line + '\n';
							}

							output = output + "Congratulations!";
							SendRecordToGroup(output);
						}
					}
                }
            }
        }
    }

	pthread_exit(NULL);
}

void SendRecordToGroup(std::string &message)
{
	std::ifstream file;
	file.open("./cfg/recordgroup.txt");

    if(!file.is_open())
    {
        std::cout << "The file cannot be opened." << std::endl;
        return;
    }

	std::string line;

	while(std::getline(file, line))
	{
		bot.SendMessage(GID_t(std::stol(line)), MessageChain().Plain(message));
		sleep(1);
	}

	file.close();
}