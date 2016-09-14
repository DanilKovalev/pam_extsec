#define PAM_SM_AUTH

#include <security/pam_modules.h>

#include "PamConversation.h"

PAM_EXTERN int pam_sm_authenticate(pam_handle_t * pamh, int flags
        ,int argc, const char **argv)
{
    const char *user_name;

    int retval = pam_get_user(pamh, &user_name, "login: ");
    if ( retval )
    {
        return PAM_ABORT;
    }


    struct pam_conv *conv;
    retval = pam_get_item( pamh, PAM_CONV, (const void **) &conv ) ;
    PamConversation conversation(conv);


//    conversation.ask();

    struct pam_conv;
    return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_setcred(pam_handle_t * pamh, int flags
        ,int argc, const char **argv)
{
    return PAM_SUCCESS;
}