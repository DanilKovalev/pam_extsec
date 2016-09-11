#include "PamResponse.h"

#include <stdexcept>
#include <cstring>

PamResponse::PamResponse(const std::string &text)
 : m_response{nullptr, 0}
{
    set_text(text);
}

PamResponse::PamResponse(struct pam_response *response)
 : m_response(*response)
{
}

PamResponse::PamResponse(const PamResponse &rhs)
 : PamResponse("")
{
    set_text( rhs.get_text() );
}

PamResponse& PamResponse::operator=(const PamResponse &rhs)
{
    if(this == &rhs)
        return *this;

    this->set_text( rhs.get_text() );
    return *this;
}


PamResponse::~PamResponse()
{
    free_responce(m_response);
}

void PamResponse::free_responce(pam_response& response ) noexcept
{
    if(response.resp)
        std::free(response.resp);

    response.resp = nullptr;
}

std::string PamResponse::get_text() const
{
    return std::string(m_response.resp);
}

void PamResponse::set_text(const std::string &text)
{
    char* old_text = m_response.resp;
    try
    {
        m_response.resp = ::strdup( text.data() );
        if (m_response.resp == nullptr)
            throw std::bad_alloc();

        std::free(old_text);
    }
    catch (std::exception& ex)
    {
        m_response.resp = old_text;
        throw;
    }
}

PamResponse::operator struct pam_response& ()
{
    return m_response;
}

PamResponse::operator const struct pam_response& () const
{
    return m_response;
}



