#define PAM_SM_AUTH

#include <security/pam_modules.h>

#include "PamConversation.h"

int pam_sm_open_session(pam_handle_t *pamh, int flags,
                                   int argc, const char **argv)
{

    return PAM_SUCCESS;
}

int pam_sm_close_session(pam_handle_t *pamh, int flags,
                                    int argc, const char **argv)
{
    return PAM_SUCCESS;
}
