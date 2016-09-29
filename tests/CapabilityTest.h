#ifndef CAPABILITYTEST_H
#define CAPABILITYTEST_H

#include "Capability.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class CapabilityTest : public CppUnit::TestCase
{
public:
    CapabilityTest(): TestCase("Capability wrapper test."), m_cap() {}
    void check_comparison();
    void check_clear();
    void check_set();
    void check_copy();
    void check_to_str();
    void check_from_str();

    void setUp()
    {
        m_cap.set_effective_flag(CAP_CHOWN);
        m_cap.set_inheritable_flag(CAP_KILL);
        m_cap.set_permitted_flag(CAP_MAC_OVERRIDE);
    }

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( CapabilityTest );
        CPPUNIT_TEST( check_set );
        CPPUNIT_TEST( check_clear );
        CPPUNIT_TEST( check_comparison );
        CPPUNIT_TEST( check_copy );
        CPPUNIT_TEST( check_to_str );
        CPPUNIT_TEST( check_from_str );
    CPPUNIT_TEST_SUITE_END();
private:
    Capability m_cap;
};



#endif // CAPABILITYTEST_H
