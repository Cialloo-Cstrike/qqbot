#ifndef CIALLOO_MIRAI_QQBOT_HPP
#define CIALLOO_MIRAI_QQBOT_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include <httplib.h>
#include <functional>
#include <fstream>
#include "cialloo/network/websocket_client.hpp"
#include <thread>

namespace cialloo {
namespace mirai {

const std::string content_type = "application/json;charset=UTF-8"; 

inline nlohmann::json receive_parser(const httplib::Result& result)
{
    nlohmann::json content = nlohmann::json::parse(result->body);

    if(content.contains("code"))
    {
        if(content["code"].get<int>())
            std::cout << "There is an error with receive_parser.\n";
    }

    return content;
}
    
class qqbot
{
public:
    qqbot(std::string config_path);
    ~qqbot();

    qqbot(const qqbot&) = delete;
    qqbot& operator=(const qqbot&) = delete;

public:
    void send_to_group(unsigned long long group_number, std::string message);
    void received_text(std::function<void(std::string)> callback);
    void run();

private:
    void verify();
    void bind();

    void parse_config();

private:
    int http_port_;
    unsigned long long qqnumber_;
    std::string session_key_;
    std::string verify_key_;
    std::string target_host_;
    nlohmann::json config_;
    std::shared_ptr<httplib::Client> http_client_;
    std::function<void(std::string)> receive_callback_;
    std::shared_ptr<cialloo::network::websocket_client> websocket_client_;
};

inline void qqbot::run()
{
    websocket_client_->run();
}

inline void qqbot::received_text(std::function<void(std::string)> callback)
{
    receive_callback_ = callback;
    websocket_client_->on_received_text(receive_callback_);
}

inline qqbot::qqbot(std::string config_path)
    : http_port_(8080),
      qqnumber_(123456789ULL),
      session_key_(""),
      target_host_("127.0.0.1"),
      receive_callback_(nullptr)
{
    std::ifstream config_file(config_path);
    config_ = nlohmann::json::parse(config_file);
    parse_config();
    verify();
    bind();
}

inline qqbot::~qqbot()
{
    nlohmann::json release_json = 
    {
        { "sessionKey", session_key_ },
        { "qq", qqnumber_ }
    };

    auto response = http_client_->Post("/release", release_json.dump(), content_type.c_str());
    receive_parser(response);
}

inline void qqbot::send_to_group(unsigned long long group_number, std::string message)
{
    nlohmann::json message_json = 
    {
        { "sessionKey", session_key_ },
        { "target", group_number }
    };

    message_json["messageChain"] = 
    {
        { { "type", "Plain" }, { "text", message } }
    };

    auto response = http_client_->Post("/sendGroupMessage", message_json.dump(), content_type.c_str());
    receive_parser(response);
}

inline void qqbot::bind()
{
    nlohmann::json bind_json = 
    {
        { "sessionKey", session_key_ },
        { "qq", qqnumber_ }
    };

    auto response = http_client_->Post("/bind", bind_json.dump(), content_type.c_str());
    receive_parser(response);
}

inline void qqbot::verify()
{
    nlohmann::json verify_json = 
    {
        { "verifyKey", verify_key_ }
    };

    auto response = http_client_->Post("/verify", verify_json.dump(), content_type.c_str());
    nlohmann::json response_json = receive_parser(response);
    session_key_ = response_json["session"].get<std::string>();
}

inline void qqbot::parse_config()
{
    http_port_ = config_["port"].get<int>();
    qqnumber_ = config_["qqnumber"].get<unsigned long long>();
    target_host_ = config_["hostname"].get<std::string>();
    verify_key_ = config_["verifykey"].get<std::string>();
    http_client_ = std::make_shared<httplib::Client>(target_host_, http_port_);

    std::string handshake_path = "message?verifyKey=" + verify_key_ + "&qq=" + std::to_string(qqnumber_);
    websocket_client_ = std::make_shared<cialloo::network::websocket_client>(target_host_, http_port_, handshake_path);
    websocket_client_->on_received_text(receive_callback_);
}


} // namespace mirai
} // namespace cialloo



#endif // CIALLOO_MIRAI_QQBOT_HPP