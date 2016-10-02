#include "Syslog.h"

Syslog& Syslog::get()
{
    static Syslog instance;
    return instance;
}
