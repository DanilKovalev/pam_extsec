#include "CommandLine.h"

namespace po = boost::program_options;

#define DEFAULT_CONF_PATH "/etc/security/pam_stepic.conf"

void CommandLine::parse_option( int argc, const char **argv )
{
    po::options_description desc( "Allowed options", 1024 );
    desc.add_options()
            ( "config-file", po::value<std::string>()->default_value( DEFAULT_CONF_PATH ), "Config file path" )
            ( "generic", po::value<std::vector<std::string>>(), "Generic Arguments" );
    po::positional_options_description p;
    p.add( "generic", -1 );
    po::command_line_parser cmd( argc, argv );
    cmd.options( desc );
    cmd.positional( p );
    try
    {
        po::store( cmd.run(), m_vm );
        m_vm.notify();
    }
    catch ( std::exception &e )
    {
        throw;
    }
}

bool CommandLine::is_debug() const noexcept
{
    return is_generic_argument_set("debug");
}

bool CommandLine::is_expose_account() const noexcept
{
    return is_generic_argument_set("expose_account");
}

bool CommandLine::is_no_warn() const noexcept
{
    return is_generic_argument_set("no_warn");
}

bool CommandLine::is_try_first_pass() const noexcept
{
    return is_generic_argument_set("try_first_pass");
}

bool CommandLine::is_use_first_pass() const noexcept
{
    return is_generic_argument_set("use_first_pass");
}

bool CommandLine::is_use_mapped_pass() const noexcept
{
    return is_generic_argument_set("use_mapped_pass");
}

std::string CommandLine::get_config_file_path() const noexcept
{
    return m_vm["config-file"].as<std::string>();
}

bool CommandLine::is_generic_argument_set( const std::string& argument ) const noexcept
{
    auto generic = m_vm["generic"].as<std::vector<std::string>>();
    auto iter = std::find( generic.begin(), generic.end(), argument );

    return iter != generic.end();
}
