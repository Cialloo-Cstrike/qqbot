#ifndef QQBOT_H
#define QQBOT_H

#include <string>

void* SendNull(void* args);

// this structure can only be used by server.
struct player_info
{
    char name[64];
    char steamid[64];
};


struct css_server
{
    char ip[64];
    char name[128];
    char map[256];
    int port;
    int player_count;
    std::vector<player_info> player_list;
};

#endif