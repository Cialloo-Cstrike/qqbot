#include <iostream>
#include <map>
#include <mirai.h>
#include "myheader.h"
using namespace std;
using namespace Cyan;

extern MiraiBot bot;

void OnSocketReceiveMsg(int sockfd, const char* buffer)
{
    std::stringstream message(buffer);
    std::string line, output;
    std::getline(message, line);

    switch(std::stoi(line))
    {
        case NULLMSG:
        {
            send(sockfd, "0", 8, 0);
            break;
        }
        case SURFWR:
        case SURFFINISH:
        case BHOPWR:
        case BHOPFINISH:
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