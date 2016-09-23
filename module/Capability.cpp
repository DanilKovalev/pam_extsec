#include <exception>
#include <system_error>
#include <memory>
#include <string.h>
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
        free_cap(m_cap);
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
            copy_cap(rhs.m_cap);

        free_cap(old_cap);
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
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to copy capability." );

    return ret;
}

void Capability::free_cap(cap_t cap)
{
    if( !cap )
        return;

    if ( cap_free(cap) )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to clear capability." );
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
    std::unique_ptr<char, decltype(cap_free)*> ptrText(cap_to_text(m_cap, &szText), cap_free);
    if (!ptrText)
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to convert capability to text.");

    return std::string(ptrText.get(), szText);
}

void Capability::set_inheritable_flag()
{
    CAP_CHOWN
    if( cap_set_flag() )
}

void Capability::clear_inheritable_flag()
{

}



