#include "PamMessage.h"

#include <stdexcept>
#include <cstring>

PamMessage::PamMessage(const std::string &text)
 : pam_message{0, nullptr}
{
    set_text(text);
    msg_style = 0;
}

PamMessage::PamMessage(const pam_message& message)
 : pam_message(message)
{
}

PamMessage::PamMessage(const PamMessage &rhs)
 : pam_message{0, nullptr}
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

PamMessage& PamMessage::operator=( const pam_message* message )
{
    if(msg)
        free((char*)msg);

    msg = message->msg;
    msg_style = message->msg_style;
    return *this;
}

PamMessage::~PamMessage()
{
    if(msg)
        free((char*)msg);
}

void PamMessage::set_text(const std::string &text)
{
    const char* old_text = msg;
    try
    {
        if (text.length() + 1 > PAM_MAX_MSG_SIZE )
            throw std::runtime_error("Invalid message text size.");

        msg = ::strdup( text.data() );
        if( msg == nullptr )
            throw std::bad_alloc();

        std::free((char*)old_text);
    }
    catch (std::exception& ex)
    {
        msg = old_text;
        throw;
    }
}

PamMessage::operator struct pam_message* ()
{
    return this;
}

PamMessage::operator const struct pam_message* () const
{
    return this;
}

std::string PamMessage::get_text() const
{
    return msg;
}

int PamMessage::get_style() const noexcept
{
    return msg_style;
}

void PamMessage::set_style(int style) noexcept
{
    msg_style = style;
}




