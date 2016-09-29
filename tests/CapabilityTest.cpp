#include "CapabilityTest.h"

void CapabilityTest::check_comparison()
{
    CPPUNIT_ASSERT( m_cap == m_cap  );
    CPPUNIT_ASSERT( m_cap != Capability::from_proc() );
}

void CapabilityTest::check_clear()
{
    Capability cap = Capability::from_proc();

    CPPUNIT_ASSERT( !cap.is_effective_flag_set(CAP_CHOWN) );
    CPPUNIT_ASSERT( !cap.is_inheritable_flag_set(CAP_KILL) );
    CPPUNIT_ASSERT( !cap.is_permitted__flag_set(CAP_MAC_OVERRIDE) );
}

void CapabilityTest::check_set()
{
    Capability cap = Capability::from_proc();
    cap.set_effective_flag(CAP_SETGID);
    cap.set_inheritable_flag(CAP_NET_RAW);
    cap.set_permitted_flag(CAP_SYSLOG);

    CPPUNIT_ASSERT( cap.is_effective_flag_set(CAP_SETGID) );
    CPPUNIT_ASSERT( cap.is_inheritable_flag_set(CAP_NET_RAW) );
    CPPUNIT_ASSERT( cap.is_permitted__flag_set(CAP_SYSLOG) );
}

void CapabilityTest::check_copy()
{
    Capability cap (m_cap);
    CPPUNIT_ASSERT( m_cap == cap );

    Capability cap2;
    cap2 = cap;
    CPPUNIT_ASSERT( m_cap == cap2 );
}

void CapabilityTest::check_to_str()
{
    CPPUNIT_ASSERT( m_cap.to_text() == "= cap_kill+i cap_mac_override+p cap_chown+e");
}

void CapabilityTest::check_from_str()
{
    CPPUNIT_ASSERT( m_cap == Capability::from_text("= cap_kill+i cap_mac_override+p cap_chown+e") );
}

