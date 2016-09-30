#ifndef LIBCAPWRAPPER_H
#define LIBCAPWRAPPER_H


#include <sys/capability.h>

namespace libcap
{
    cap_t cap_dup( const cap_t cap );
    cap_t cap_init();
    void cap_free( cap_t cap );
    void cap_set_flag( cap_t, cap_flag_t, cap_value_t, cap_flag_value_t );
    bool cap_is_flag_set( cap_t, cap_value_t, cap_flag_t );
    bool cap_is_flag_set( cap_t, cap_value_t, cap_flag_t );
}

#endif // LIBCAPWRAPPER_H
