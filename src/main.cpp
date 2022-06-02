#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <ssq/a2s.h>
#include <cialloo/mirai/qqbot.hpp>

std::string get_host_info(std::string ip, int port)
{
    std::string output{};
    ssq_querier *querier = ssq_init();
    ssq_set_timeout(querier, SSQ_TIMEOUT_RECV, 3000);
    ssq_set_timeout(querier, SSQ_TIMEOUT_SEND, 3000);

    ssq_set_target(querier, ip.c_str(), port);

    uint8_t player_count = 0;
    a2s_info *info = ssq_info(querier);

    if (!ssq_ok(querier)) 
    {
        const char *error_message = ssq_errm(querier);
        fprintf(stderr, "ssq_info: %s\n", error_message);

        ssq_errclr(querier);

        return output;
    }

    a2s_player *players = ssq_player(querier, &player_count);

    if (!ssq_ok(querier)) 
    {
        const char *error_message = ssq_errm(querier);
        fprintf(stderr, "ssq_info: %s\n", error_message);

        ssq_errclr(querier);

        return output;
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

    ssq_info_free(info);
    ssq_player_free(players, player_count);

    return output;
}

int main(int argc, char* args[])
{
    cialloo::mirai::qqbot bot("config/config.json");
    std::ifstream group_json("./config/group_settings.json");
    nlohmann::json group_settings = nlohmann::json::parse(group_json);
    bot.received_text([&](std::string message) {
        auto message_json = nlohmann::json::parse(message);

        if(message_json["data"]["type"].get<std::string>() == "GroupMessage")   // check if group msg
        {
            auto group_number = message_json["data"]["sender"]["group"]["id"].get<unsigned long long>();
            std::string group_str = std::to_string(group_number);

            if(group_settings.contains(group_str)) // check have group config.
            {
                if(group_settings["data"]["messageChain"].size() >= 2) // check if this has a plain text
                {
                    nlohmann::json text = group_settings["data"]["messageChain"].at(1);

                    if(text["type"].get<std::string>() == "Plain") // check what type it is
                    {
                        std::string keyword = text["text"].get<std::string>();

                        if(group_settings[group_str].contains(keyword)) // check if group has this keyword
                        {
                            std::string ip = group_settings[group_str][keyword]["ip"].get<std::string>();
                            int port = group_settings[group_str][keyword]["port"].get<int>();
                            std::string output = get_host_info(ip, port);

                            if(output.size() > 0)
                                bot.send_to_group(group_number, output);
                            else
                                bot.send_to_group(group_number, "Error query.");
                        }
                    }
                }
            }
        }
    });
}