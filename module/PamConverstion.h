#ifndef PAMCONVERSATION_H
#define PAMCONVERSATION_H

#include <security/pam_modules.h>

class PamConverstion
{
public:
    explicit PamConverstion( struct pam_conv *conv);
    ~PamConverstion() = default;
private:
    struct pam_conv *m_conv;
};


#endif // PAMCONVERSATION_H
