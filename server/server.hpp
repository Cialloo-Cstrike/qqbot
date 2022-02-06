#ifndef QQBOT_H
#define QQBOT_H

#include <string>

void* SendNull(void* args);

struct css_server
{
    char map[256];
    int player_count;
    std::vector<std::string> player_list;
};

#endif