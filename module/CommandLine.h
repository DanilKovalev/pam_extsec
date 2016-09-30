#ifndef COMMANDLINE_H
#define COMMANDLINE_H


#include <boost/program_options.hpp>

class CommandLine {
public:
    CommandLine() : m_vm() {};

    void parse_option( int argc, const char **argv );

    bool is_debug() const noexcept;
    bool is_expose_account() const noexcept;
    bool is_no_warn() const noexcept;
    bool is_try_first_pass() const noexcept;
    bool is_use_first_pass() const noexcept;
    bool is_use_mapped_pass() const noexcept;

    std::string get_config_file_path() const noexcept ;
private:
    bool is_generic_argument_set(const std::string& argument) const noexcept;

    boost::program_options::variables_map m_vm;
};


#endif // COMMANDLINE_H
