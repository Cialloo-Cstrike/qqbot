#ifndef CIALLOO_CSTRIKE_RECEIVE_PARSER_HPP
#define CIALLOO_CSTRIKE_RECEIVE_PARSER_HPP

#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>

namespace cialloo {
namespace cstrike {

nlohmann::json receive_parser(const httplib::Result& result)
{
    nlohmann::json content = nlohmann::json::parse(result->body);

    if(content.contains("code"))
    {
        if(content["code"].get<int>())
            std::cout << "There is an error with receive_parser.\n";
    }

    return content;
}

} // namespace cstrike
} // namespace cialloo


#endif // CIALLOO_CSTRIKE_RECEIVE_PARSER_HPP