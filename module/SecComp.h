#ifndef SECCOMP_H
#define SECCOMP_H


#include <seccomp.h>

#include <string>

class SecComp
{
public:
    SecComp();
    ~SecComp();

    void destroy();

    void add_forbidden( const std::string &syscall_name );
    void add_allow( const std::string &syscall_name );

    void load();

private:

    scmp_filter_ctx m_scmp_ctx;
};


#endif // SECCOMP_H
