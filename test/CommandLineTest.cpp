#include "CommandLineTest.h"

#include "CommandLine.h"


void CommandLineTest::check_parse1()
{
    const char *argv[] = {"executing_path", "1"};
    const int argc = sizeof( argv ) / sizeof( char * );

    CommandLine cli;
    cli.parse_option( argc, argv );
    CPPUNIT_ASSERT( !cli.is_debug() );
}

void CommandLineTest::check_parse2()
{
    const char *argv[] = {"executing_path", "debug", "expose_account", "no_warn", "try_first_pass", "use_first_pass", "use_mapped_pass"};
    const int argc = sizeof( argv ) / sizeof( char * );

    CommandLine cli;
    cli.parse_option( argc, (const char **) argv );
    CPPUNIT_ASSERT( cli.is_debug() );
    CPPUNIT_ASSERT( cli.is_expose_account() );
    CPPUNIT_ASSERT( cli.is_no_warn() );
    CPPUNIT_ASSERT( cli.is_try_first_pass() );
    CPPUNIT_ASSERT( cli.is_use_first_pass() );
    CPPUNIT_ASSERT( cli.is_use_mapped_pass() );
}

void CommandLineTest::check_parse3()
{
    const char *argv[] = {"executing_path", "--config-file", "/tmp.conf"};
    const int argc = sizeof( argv ) / sizeof( char * );

    CommandLine cli;
    cli.parse_option( argc, (const char **) argv );
    CPPUNIT_ASSERT( cli.get_config_file_path() ==  "/tmp.conf");

}
