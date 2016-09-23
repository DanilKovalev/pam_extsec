#ifndef CAPABILITY_H
#define CAPABILITY_H

#include <string>

#include <sys/capability.h>

class Capability
{
public:
    Capability(cap_t cap);
    Capability(const Capability& rhs);
    Capability& operator = (const Capability& rhs);
    ~Capability();

    inline cap_t get() noexcept;
    inline const _cap_struct* get() const noexcept;
    void set_proc( );

    std::string to_text() const;

    void set_inheritable_flag();
    void clear_inheritable_flag();

    static Capability from_text(const std::string& text);
    static Capability from_proc(pid_t pid = 0);

private:
    static cap_t copy_cap(const cap_t cap);
    static void free_cap(cap_t cap);

private:
    cap_t m_cap;
};


#endif //PAM_STEPIC_CAPABILITY_H
