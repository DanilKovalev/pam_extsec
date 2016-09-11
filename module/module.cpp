#define PAM_SM_AUTH

#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t * pamh, int flags
        ,int argc, const char **argv)
{
    const char *user_name;

    int retval = pam_get_user(pamh, &user_name, "login: ");
    if ( retval )
    {

    }

    struct pam_conv;
    return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_setcred(pam_handle_t * pamh, int flags
        ,int argc, const char **argv)
{
    return PAM_SUCCESS;
}