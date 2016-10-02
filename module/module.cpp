#define PAM_SM_AUTH

#include "Syslog.h"
#include "PamLogging.h"
#include "ConfigFile.h"
#include "CommandLine.h"

#include <security/pam_modules.h>

int pam_sm_open_session(pam_handle_t *pamh, int flags,
                                   int argc, const char **argv)
{
    (void)(pamh);

    try
    {
        if(flags & PAM_SILENT)
            pam_log->set_silent( true );

        CommandLine cli;
        cli.parse_option(argc, argv);

        pam_log->set_debug( cli.is_debug() );
        pam_log->set_no_warn( cli.is_no_warn() );

        ConfigFile configFile( cli.get_config_file_path() );
    }
    catch (std::exception& ex)
    {
        pam_log->write_err( ex.what() );
        return PAM_ABORT;
    }
    return PAM_SUCCESS;
}

int pam_sm_close_session(pam_handle_t *pamh, int flags,
                                    int argc, const char **argv)
{
    (void)(pamh);
    (void)(flags);
    (void)(argc);
    (void)(argv);

    return PAM_SUCCESS;
}
