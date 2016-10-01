#ifndef CAPABILITY_H
#define CAPABILITY_H


#include <string>
#include <utility>

#include <sys/capability.h>

using namespace std::rel_ops;

class Capability
{
public:
    Capability();
    Capability(cap_t cap);
    Capability(const Capability& rhs);
    Capability& operator = (const Capability& rhs);
    ~Capability();

    void destroy();

    inline cap_t get() noexcept;
    inline const _cap_struct* get() const noexcept;
    void set_proc( void );

    std::string to_text() const;

    void set_inheritable_flag(cap_value_t cap_value);
    void clear_inheritable_flag(cap_value_t cap_value);
    bool is_inheritable_flag_set(cap_value_t cap_value) const;

    void set_effective_flag(cap_value_t cap_value);
    void clear_effective_flag(cap_value_t cap_value);
    bool is_effective_flag_set(cap_value_t cap_value) const;

    void set_permitted_flag(cap_value_t cap_value);
    void clear_permitted_flag(cap_value_t cap_value);
    bool is_permitted__flag_set(cap_value_t cap_value) const;

    friend
    bool operator==( const Capability &lhs, const Capability &rhs );

    static Capability from_text(const std::string& text);
    static Capability from_proc(pid_t pid = 0);

private:
    cap_t m_cap;
};


#endif //PAM_STEPIC_CAPABILITY_H
