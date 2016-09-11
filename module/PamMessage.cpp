#include "PamMessage.h"

#include <stdexcept>
#include <cstring>

PamMessage::PamMessage(const std::string &text)
 : m_message{0, nullptr}
{
    set_text(text);
}

PamMessage::PamMessage(const PamMessage &rhs)
 : m_message{0, nullptr}
{
    set_text( rhs.get_text() );
    set_style( rhs.get_style() );
}

PamMessage &PamMessage::operator=(const PamMessage &rhs)
{
    if(this == &rhs)
        return *this;

    set_text(rhs.get_text());
    set_style(rhs.get_style() );

    return *this;
}


PamMessage::~PamMessage()
{
    free_message();
}

void PamMessage::set_text(const std::string &text)
{
    const char* old_text = m_message.msg;
    try
    {
        if (text.length() + 1 > PAM_MAX_MSG_SIZE || text.empty() )
            throw std::runtime_error("Invalid message text size.");

        m_message.msg = ::strdup( text.data() );
        if( m_message.msg == nullptr )
            throw std::bad_alloc();

        std::free((char*)m_message.msg);
    }
    catch (std::exception& ex)
    {
        m_message.msg = old_text;
        throw;
    }
}

PamMessage::operator struct pam_message& ()
{
    return m_message;
}

PamMessage::operator const struct pam_message& () const
{
    return m_message;
}

std::string PamMessage::get_text() const
{
    return m_message.msg;
}

void PamMessage::free_message() noexcept
{
    if( m_message.msg )
        std::free((char*)m_message.msg);

    m_message.msg = nullptr;
}

int PamMessage::get_style() const noexcept
{
    return m_message.msg_style;
}

void PamMessage::set_style(int style) noexcept
{
    m_message.msg_style = style;
}




