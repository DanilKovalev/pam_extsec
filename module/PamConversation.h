#ifndef PAMCONVERSATION_H
#define PAMCONVERSATION_H

#include "CArrayWrapper.h"
#include "PamMessage.h"
#include "PamResponse.h"

#include <security/pam_modules.h>

#include <vector>

class PamConversation : private pam_conv
{
public:
    explicit PamConversation( struct pam_conv *conv);
    PamConversation( const PamConversation& rhs) = delete;
    PamConversation operator = ( const PamConversation& rhs) = delete;

    operator pam_conv* ();
    operator const pam_conv* () const;

    CArrayWrapper<pam_response> ask(const CArrayWrapper<pam_message>& messages);
    std::vector<PamResponse> ask(const std::vector<PamMessage>& messages);

};





#endif // PAMCONVERSATION_H
