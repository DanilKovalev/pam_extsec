#include "SecCompTest.h"
#include "SecComp.h"

void SecCompTest::check_forbidden()
{
    SecComp scmp;
    CPPUNIT_ASSERT_NO_THROW(scmp.add_forbidden("close"));
    CPPUNIT_ASSERT_THROW(scmp.add_forbidden("not_exist_syscall"), std::exception);
}

