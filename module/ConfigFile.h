#ifndef PAM_STEPIC_CONFIG_H
#define PAM_STEPIC_CONFIG_H

#include "Capability.h"

#include <jsoncpp/json/json.h>
#include <string>
#include <map>

struct config
{
    std::vector<std::string> capability;
    std::vector<std::string> syscalls;
};

class ConfigFile
{
public:
    ConfigFile(const std::string& path);

    struct config get_config(const std::string& tty) const;
    bool find_config(const std::string& tty, struct config&) const noexcept;

private:
    std::map<std::string, config> parse_config(const std::string &path);
    config parse_object(const Json::Value obj);
    std::vector<std::string> parse_array(const Json::Value obj);

private:
    std::map<std::string, config> m_ttys_configs;
};

#endif //PAM_STEPIC_CONFIG_H
