#include "LibCapWrapper.h"

#include <system_error>

cap_t libcap::cap_dup( const cap_t cap )
{
    cap_t ret = ::cap_dup( cap );
    if( !ret )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to copy capability" );

    return ret;
}

cap_t libcap::cap_init()
{
    cap_t cap = ::cap_init();
    if( !cap )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to initialize new capability" );

    return cap;
}

void libcap::cap_free( cap_t cap )
{
    if( !cap )
        return;

    if ( ::cap_free(cap) )
        throw std::system_error( std::error_code(errno, std::generic_category() ), "Unable to free capability" );
}

void libcap::cap_set_flag( cap_t cap, cap_flag_t cap_flag, cap_value_t cap_value, cap_flag_value_t cap_flag_value)
{
    if ( ::cap_set_flag(cap, cap_flag, 1, &cap_value, cap_flag_value) )
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to set capability flag.");
}

bool libcap::cap_is_flag_set( cap_t cap, cap_value_t cap_value, cap_flag_t cap_flag)
{
    cap_flag_value_t cap_flags_value;
    if ( ::cap_get_flag(cap, cap_value, cap_flag, &cap_flags_value) )
        throw std::system_error(std::error_code(errno, std::generic_category()),
                                "Unable to get capability flag.");

    return cap_flags_value == CAP_SET;
}
