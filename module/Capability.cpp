#include <exception>
#include <system_error>
#include "Capability.h"

Capability::Capability(cap_t cap)
: m_cap(cap)
{}

Capability::Capability(const Capability &rhs)
: m_cap(nullptr)
{
    if( rhs.m_cap )
        copy_cap(rhs.m_cap);
}

Capability::~Capability()
{
    try
    {
        clear_cap(m_cap);
    }
    catch (...)
    {
    }
}

inline cap_t Capability::get() noexcept
{
    return m_cap;
}

Capability& Capability::operator=(const Capability &rhs)
{
    if(this == &rhs)
        return *this;

    cap_t old_cap = m_cap;
    try
    {
        if(rhs.m_cap)
            copy_cap(rhs.m_cap);

        clear_cap(old_cap);
        return *this;
    }
    catch (std::exception& ex)
    {
        m_cap = old_cap;
        throw;
    }
}

cap_t Capability::copy_cap(const cap_t cap)
{
    cap_t ret = cap_copy_int( cap );
    if( !ret )
        std::system_error( std::error_code(errno, std::generic_category() ), "Unable to copy capability." );

    return ret;
}

void Capability::clear_cap(cap_t cap)
{
    if( !cap )
        return;

    if ( cap_clear(cap) )
        std::system_error( std::error_code(errno, std::generic_category() ), "Unable to clear capability." );
}

Capability Capability::get_proc(pid_t pid)
{
    cap_t cap = cap_get_pid(pid);
    if( !cap )
        std::system_error( std::error_code(errno, std::generic_category() ), "Unable to get capability for process." );

    return Capability(cap);
}


