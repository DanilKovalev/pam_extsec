#ifndef SECCOMPTEST_H
#define SECCOMPTEST_H


#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class SecCompTest : public CppUnit::TestCase
{
public:
    SecCompTest(): TestCase("SecCompTest.")  {}
    void check_forbidden();

    CPPUNIT_TEST_SUITE( SecCompTest );
        CPPUNIT_TEST( check_forbidden );
    CPPUNIT_TEST_SUITE_END();
};


#endif // SECCOMPTEST_H
