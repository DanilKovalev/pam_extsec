#include "ConfigFile.h"

#include "PamLogging.h"

#include <fstream>

ConfigFile::ConfigFile(const std::string &path)
:m_ttys_configs(parse_config(path))
{}

std::map<std::string, config> ConfigFile::parse_config(const std::string &path)
{
    std::fstream config_file (path, std::fstream::in );
    if( !config_file.is_open() )
        throw std::runtime_error ( "Unable to open config file." );

    Json::Value root;
    Json::Reader reader;
    if ( !reader.parse( config_file, root ) )
        throw std::runtime_error( reader.getFormatedErrorMessages() );

    std::map<std::string, config> ttys_config;
    for(const std::string& key : root.getMemberNames())
    {
        Json::Value elem = root[key];
        ttys_config[key] = parse_object(elem);
    }

    return ttys_config;
}

config ConfigFile::parse_object(const Json::Value obj)
{
    struct config ret_config;
    auto capabilities =  obj["capabilities"];
    if( !capabilities.isNull() )
    {
        if( capabilities.isArray() )
            ret_config.capability = parse_array(capabilities);
        else
            pam_log->write_warn("Bad config file format.");
    }

    auto syscalls =  obj["syscalls"];
    if( !syscalls.isNull() )
    {
        if( syscalls.isArray() )
            ret_config.syscalls = parse_array(syscalls);
        else
            pam_log->write_warn("Bad config file format.");
    }

    return ret_config;
}

std::vector<std::string> ConfigFile::parse_array(const Json::Value obj)
{
    std::vector<std::string> vector;
    for ( const auto& elem : obj )
        vector.push_back(elem.asString());

    return vector;
}

struct config ConfigFile::get_config(const std::string& tty) const
{
    struct config config;
    if( find_config(tty, config) )
        return config;

    throw std::runtime_error("Unable to get config for tty.");
}

bool ConfigFile::find_config(const std::string& tty, struct config& config) const noexcept
{
    auto conf_iter = m_ttys_configs.find(tty);
    if( conf_iter == m_ttys_configs.end() )
        return false;

    config = (*conf_iter).second;
    return true;
}




