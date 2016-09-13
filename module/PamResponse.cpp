#include "PamResponse.h"

#include <stdexcept>
#include <cstring>

PamResponse::PamResponse(const std::string &text)
{
    set_text(text);
    resp_retcode = 0;
}

PamResponse::PamResponse(const pam_response* response)
{
    resp = response->resp;
    resp_retcode = 0;
}

PamResponse::PamResponse(const PamResponse &rhs)
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
    if(resp)
        std::free(resp);

    resp = nullptr;
}

std::string PamResponse::get_text() const
{
    return std::string(resp);
}

void PamResponse::set_text(const std::string &text)
{
    char* old_text = resp;
    try
    {
        resp = ::strdup( text.data() );
        if (resp == nullptr)
            throw std::bad_alloc();

        std::free(old_text);
    }
    catch (std::exception& ex)
    {
        resp = old_text;
        throw;
    }
}

PamResponse::operator struct pam_response* ()
{
    return this;
}

PamResponse::operator const struct pam_response* () const
{
    return this;
}



