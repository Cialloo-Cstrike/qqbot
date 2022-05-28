#ifndef CIALLOO_CSTRIKE_QQBOT_HPP
#define CIALLOO_CSTRIKE_QQBOT_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include <httplib.h>

namespace cialloo {
namespace cstrike {

const std::string content_type = "application/json;charset=UTF-8"; 
    
class qqbot
{
public:
    qqbot(std::string config_path);
    ~qqbot();

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
};


} // namespace cstrike
} // namespace cialloo



#endif // CIALLOO_CSTRIKE_QQBOT_HPP