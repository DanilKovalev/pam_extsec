#include "SecComp.h"

#include "PamLogging.h"

#include <seccomp.h>
#include <system_error>

SecComp::SecComp()
: m_scmp_ctx( nullptr)
{
    m_scmp_ctx = seccomp_init( SCMP_ACT_ALLOW );
    if( !m_scmp_ctx )
        throw std::system_error( std::error_code(errno, std::generic_category()),
                                 "Unable to initialize seccomp context." );
}

void SecComp::destroy()
{
    if( !m_scmp_ctx )
        return;

    seccomp_release(m_scmp_ctx);
    m_scmp_ctx = nullptr;
}

SecComp::~SecComp()
{
    try
    {
        destroy();
    }
    catch (std::exception& ex)
    {
        pam_log->write_warn("Unable to destroy object seccomp.");
        pam_log->write_warn(ex.what());
    }
}

void SecComp::add_forbidden( const std::string &syscall_name )
{
    int syscall = seccomp_syscall_resolve_name( syscall_name.data() );
    if ( syscall == __NR_SCMP_ERROR )
        throw std::runtime_error( "Unable to resolve syscall name." );

    if ( seccomp_rule_add(m_scmp_ctx, SCMP_ACT_TRAP, syscall, 0) )
        throw std::system_error( std::error_code(errno, std::generic_category()),
                                 "Unable to add rule to seccomp context." );
}

void SecComp::add_allow( const std::string &syscall_name )
{
    int syscall = seccomp_syscall_resolve_name( syscall_name.data() );
    if ( syscall == __NR_SCMP_ERROR )
        throw std::runtime_error( "Unable to resolve syscall name." );

    if ( seccomp_rule_add(m_scmp_ctx, SCMP_ACT_ALLOW, syscall, 0) )
        throw std::system_error( std::error_code(errno, std::generic_category()),
                                 "Unable to add rule to seccomp context." );
}

void SecComp::load()
{
    if ( seccomp_load(m_scmp_ctx) )
        throw std::system_error( std::error_code(errno, std::generic_category()),
                                 "Unable to load seccomp context." );
}

