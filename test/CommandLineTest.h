#ifndef COMMANDLINETEST_H
#define COMMANDLINETEST_H


#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class CommandLineTest : public CppUnit::TestCase
{
public:
    CommandLineTest() : TestCase( "Command Line Test." )
    {}

    void check_parse1();
    void check_parse2();
    void check_parse3();

CPPUNIT_TEST_SUITE( CommandLineTest );
        CPPUNIT_TEST( check_parse1 );
        CPPUNIT_TEST( check_parse2 );
        CPPUNIT_TEST( check_parse3 );
    CPPUNIT_TEST_SUITE_END();
};


#endif //PAM_STEPIC_COMMANDLINETEST_H
