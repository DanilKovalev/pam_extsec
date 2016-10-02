#include "Syslog.h"

#include <syslog.h>

Syslog& Syslog::get()
{
    static Syslog instance;
    return instance;
}

Syslog::Syslog()
{
    openlog("pam_stepic", LOG_CONS|LOG_PID, LOG_AUTH);
}

Syslog::~Syslog()
{
    closelog();
}

void Syslog::set_silent( bool flag )
{
    m_is_silent = flag;
}

void Syslog::set_debug( bool flag )
{
    m_is_debug = flag;
}

void Syslog::set_no_warn( bool flag )
{
    m_is_no_warn = flag;
}

void Syslog::write_debug( const std::string &message )
{
    if( m_is_debug && !m_is_silent )
        syslog ( LOG_DEBUG, "%s", message.data() );
}

void Syslog::write_info( const std::string &message )
{
    if ( !m_is_silent )
        syslog ( LOG_INFO, "%s", message.data() );
}

void Syslog::write_warn( const std::string &message )
{
    if( !m_is_no_warn && !m_is_silent )
        syslog ( LOG_WARNING, "%s", message.data() );
}

void Syslog::write_err( const std::string &message )
{
    if( !m_is_silent )
        syslog ( LOG_ERR, "%s", message.data() );
}
