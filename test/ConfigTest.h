#ifndef CONFIGTEST_H
#define CONFIGTEST_H

#include "Capability.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class ConfigTest : public CppUnit::TestCase
{
public:
    ConfigTest(): TestCase("Config file test."), m_cap() {}

    void check_open();
    void check_parse();

    CPPUNIT_TEST_SUITE( ConfigTest );
        CPPUNIT_TEST( check_open );
        CPPUNIT_TEST( check_parse );
    CPPUNIT_TEST_SUITE_END();
private:
    Capability m_cap;
};



#endif // CONFIGTEST_H
