#include "qqbot.hpp"
#include <fstream>
#include <memory>
#include "receive_parser.hpp"

namespace cialloo {
namespace cstrike {

qqbot::qqbot(std::string config_path)
    : http_port_(8080),
      qqnumber_(123456789ULL),
      session_key_(""),
      target_host_("127.0.0.1")
{
    std::ifstream config_file(config_path);
    config_ = nlohmann::json::parse(config_file);
    parse_config();
    verify();
    bind();
}

qqbot::~qqbot()
{
    nlohmann::json release_json = 
    {
        { "sessionKey", session_key_ },
        { "qq", qqnumber_ }
    };

    auto response = http_client_->Post("/release", release_json.dump(), content_type.c_str());
    receive_parser(response);
}

void qqbot::send_to_group(unsigned long long group_number, std::string message)
{
    nlohmann::json message_json = 
    {
        { "sessionKey", session_key_ },
        { "target", group_number }
    };

    message_json["messageChain"] = 
    {
        { { "type", "Plain" }, { "text", message } }
    }; std::cout << message_json.dump() << std::endl;//DEBUG

    auto response = http_client_->Post("/sendGroupMessage", message_json.dump(), content_type.c_str());
    receive_parser(response);
}

void qqbot::bind()
{
    nlohmann::json bind_json = 
    {
        { "sessionKey", session_key_ },
        { "qq", qqnumber_ }
    };

    auto response = http_client_->Post("/bind", bind_json.dump(), content_type.c_str());
    receive_parser(response);
}

void qqbot::verify()
{
    nlohmann::json verify_json = 
    {
        { "verifyKey", verify_key_ }
    };

    auto response = http_client_->Post("/verify", verify_json.dump(), content_type.c_str());
    nlohmann::json response_json = receive_parser(response);
    session_key_ = response_json["session"].get<std::string>();
}

void qqbot::parse_config()
{
    http_port_ = config_["port"].get<int>();
    qqnumber_ = config_["qqnumber"].get<unsigned long long>();
    target_host_ = config_["hostname"].get<std::string>();
    verify_key_ = config_["verifykey"].get<std::string>();
    http_client_ = std::make_shared<httplib::Client>(target_host_, http_port_);
}



} // namespace cstrike    
} // namespace cialloo