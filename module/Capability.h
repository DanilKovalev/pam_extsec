#ifndef CAPABILITY_H
#define CAPABILITY_H

#include <sys/capability.h>

class Capability
{
public:
    Capability(cap_t cap);
    Capability(const Capability& rhs);
    Capability& operator = (const Capability& rhs);
    ~Capability();

    inline cap_t get() noexcept;
    static Capability get_proc( pid_t pid = 0 );
private:
    static cap_t copy_cap(const cap_t cap);
    static void  clear_cap(cap_t cap);

private:
    cap_t m_cap;
};


#endif //PAM_STEPIC_CAPABILITY_H
