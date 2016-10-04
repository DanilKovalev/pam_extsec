#ifndef SYSLOG_H
#define SYSLOG_H


#include <string>

class Syslog
{
public:
    void set_silent(bool flag = true);
    void set_debug(bool flag = true);
    void set_no_warn(bool flag = true);

    static Syslog& get();

    void write_debug(const std::string& message);
    void write_info(const std::string& message);
    void write_warn(const std::string& message);
    void write_err(const std::string& message);

private:
    Syslog();
    Syslog( const Syslog& ) = delete;
    Syslog& operator=( Syslog& ) = delete;
    ~Syslog();
private:
    bool m_is_debug = false;
    bool m_is_no_warn = false;
    bool m_is_silent = false;
};


#endif // SYSLOG_H
