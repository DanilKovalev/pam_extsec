#include "Capability.h"

#include "LibCapWrapper.h"

#include <exception>
#include <system_error>
#include <memory>
#include <string.h>

Capability::Capability()
: m_cap( libcap::cap_init() )
{}

Capability::Capability(cap_t cap)
: m_cap(cap)
{}

Capability::Capability(const Capability &rhs)
: m_cap(nullptr)
{
    if( rhs.m_cap )
        m_cap = libcap::cap_dup(rhs.m_cap);
}

Capability::~Capability()
{
    try
    {
        if(m_cap)
            destroy();
    }
    catch (...)
    {
        ///@todo: write to syslog
    }
}

void Capability::destroy()
{
    if(m_cap)
        libcap::cap_free(m_cap);

    m_cap = nullptr;
}

inline cap_t Capability::get() noexcept
{
    return m_cap;
}

inline const _cap_struct* Capability::get() const noexcept
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
            m_cap = libcap::cap_dup(rhs.m_cap);

        cap_free(old_cap);
        return *this;
    }
    catch (std::exception& ex)
    {
        m_cap = old_cap;
        throw;
    }
}

Capability Capability::from_proc(pid_t pid)
{
    cap_t cap = cap_get_pid(pid);
    if( !cap )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to get capability for process." );

    return Capability(cap);
}

Capability Capability::from_text(const std::string& text)
{
    cap_t cap = cap_from_text( text.data() );
    if( !cap )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to get capability from a text." );

    return Capability(cap);
}

void Capability::set_proc( )
{
    if( cap_set_proc(m_cap) )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to set capability for process." );
}

std::string Capability::to_text() const
{
    ssize_t szText = 0;
    std::unique_ptr<char, decltype(::cap_free)*> ptrText(cap_to_text(m_cap, &szText), ::cap_free);
    if (!ptrText)
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to convert capability to text.");

    return std::string(ptrText.get(), szText);
}

void Capability::set_inheritable_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_INHERITABLE, cap_value, CAP_SET);
}

void Capability::clear_inheritable_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_INHERITABLE, cap_value, CAP_CLEAR);
}

bool Capability::is_inheritable_flag_set(cap_value_t cap_value) const
{
    return libcap::cap_is_flag_set(m_cap, cap_value, CAP_INHERITABLE );
}

void Capability::set_effective_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_EFFECTIVE, cap_value, CAP_SET);
}

void Capability::clear_effective_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_EFFECTIVE, cap_value, CAP_CLEAR);
}

bool Capability::is_effective_flag_set(cap_value_t cap_value) const
{
    return libcap::cap_is_flag_set(m_cap, cap_value, CAP_EFFECTIVE );
}

void Capability::set_permitted_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_PERMITTED, cap_value, CAP_SET);
}

void Capability::clear_permitted_flag(cap_value_t cap_value)
{
    libcap::cap_set_flag(m_cap, CAP_PERMITTED, cap_value, CAP_CLEAR);
}

bool Capability::is_permitted__flag_set(cap_value_t cap_value) const
{
    return libcap::cap_is_flag_set(m_cap, cap_value, CAP_PERMITTED );
}

bool operator == (const Capability& lhs, const Capability& rhs)
{
    if( &lhs == &rhs )
        return true;

    return !cap_compare(lhs.m_cap, rhs.m_cap);
}







