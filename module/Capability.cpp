#include <exception>
#include <system_error>
#include <memory>
#include <string.h>
#include "Capability.h"

Capability::Capability()
: m_cap(cap_init() )
{}

Capability::Capability(cap_t cap)
: m_cap(cap)
{}

Capability::Capability(const Capability &rhs)
: m_cap(nullptr)
{
    if( rhs.m_cap )
        m_cap = copy_cap(rhs.m_cap);
}

Capability::~Capability()
{
    try
    {
        cap_free(m_cap);
    }
    catch (...)
    {
    }
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
            m_cap = copy_cap(rhs.m_cap);

        cap_free(old_cap);
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
    cap_t ret = cap_dup( cap );
    if( !ret )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to copy capability." );

    return ret;
}

void Capability::cap_free(cap_t cap)
{
    if( !cap )
        return;

    if ( ::cap_free(cap) )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to clear capability." );
}

cap_t Capability::cap_init()
{
    cap_t cap = ::cap_init();
    if( !cap )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to initialize new capability." );

    return cap;
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
    cap_set_flag(m_cap, CAP_INHERITABLE, cap_value, CAP_SET);
}

void Capability::clear_inheritable_flag(cap_value_t cap_value)
{
    cap_set_flag(m_cap, CAP_INHERITABLE, cap_value, CAP_CLEAR);
}

bool Capability::is_inheritable_flag_set(cap_value_t cap_value) const
{
    return cap_get_flag(m_cap, cap_value, CAP_INHERITABLE );
}

void Capability::set_effective_flag(cap_value_t cap_value)
{
    cap_set_flag(m_cap, CAP_EFFECTIVE, cap_value, CAP_SET);
}

void Capability::clear_effective_flag(cap_value_t cap_value)
{
    cap_set_flag(m_cap, CAP_EFFECTIVE, cap_value, CAP_CLEAR);
}

bool Capability::is_effective_flag_set(cap_value_t cap_value) const
{
    return cap_get_flag(m_cap, cap_value, CAP_EFFECTIVE );
}

void Capability::set_permitted_flag(cap_value_t cap_value)
{
    cap_set_flag(m_cap, CAP_PERMITTED, cap_value, CAP_SET);
}

void Capability::clear_permitted_flag(cap_value_t cap_value)
{
    cap_set_flag(m_cap, CAP_PERMITTED, cap_value, CAP_CLEAR);
}

bool Capability::is_permitted__flag_set(cap_value_t cap_value) const
{
    return cap_get_flag(m_cap, cap_value, CAP_PERMITTED );
}

void Capability::cap_set_flag(cap_t cap, cap_flag_t flag, cap_value_t cap_value, cap_flag_value_t flag_value)
{
    if ( ::cap_set_flag(cap, flag, 1, &cap_value, flag_value) )
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to set capability flag.");
}

bool operator == (const Capability& lhs, const Capability& rhs)
{
    if( &lhs == &rhs )
        return true;

    return !cap_compare(lhs.m_cap, rhs.m_cap);
}

bool Capability::cap_get_flag(cap_t cap, cap_value_t cap_value, cap_flag_t cap_flag)
{
    cap_flag_value_t cap_flags_value;
    if ( ::cap_get_flag(cap, cap_value, cap_flag, &cap_flags_value) )
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to get capability flag.");

    return cap_flags_value == CAP_SET;
}






