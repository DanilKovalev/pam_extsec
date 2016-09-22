#include "PamConversation.h"

#include <boost/numeric/conversion/cast.hpp>

PamConversation::PamConversation(struct pam_conv *conv)
 : pam_conv(*conv)
{
}

PamConversation::operator pam_conv* ()
{
    return this;
}

PamConversation::operator const pam_conv* () const
{
    return this;
}

CArrayWrapper<pam_response> PamConversation::ask(const CArrayWrapper<pam_message> &messages)
{
    const pam_message *mes = messages;
    pam_response *resp;

    int retval = conv(boost::numeric_cast<int>(messages.size()), &mes, &resp, appdata_ptr);
    if(retval)
        throw std::runtime_error( std::to_string(retval) );


    return std::move(CArrayWrapper<pam_response>(resp, messages.size()));
}

std::vector<PamResponse> PamConversation::ask(const std::vector<PamMessage> &messages)
{
    ///@todo: optimize me
    CArrayWrapper<pam_message> wrap_messages(messages.size());
    for(size_t i = 0; i < messages.size(); i++)
        wrap_messages[i] = *messages[i];

    CArrayWrapper<pam_response> wrap_responses = ask(wrap_messages);
    std::vector<PamResponse> responses(wrap_responses.size());
    for(size_t i = 0; i < wrap_responses.size(); i++)
        responses[i] = wrap_responses[i];

    return responses;
}

