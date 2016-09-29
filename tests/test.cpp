#include "CapabilityTest.h"
#include "SecCompTest.h"

#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/CompilerOutputter.h>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CapabilityTest, "CapabilityTest Name" );
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( SecCompTest, "SecCompTest Name" );

int main()
{
    CppUnit::Test *test =
            CppUnit::TestFactoryRegistry::getRegistry("CapabilityTest Name").makeTest();

    CppUnit::Test *test2 =
            CppUnit::TestFactoryRegistry::getRegistry("SecCompTest Name").makeTest();

    CppUnit::TextTestRunner runner;

    runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr ) );

    runner.addTest(test);
    runner.addTest(test2);

    return !runner.run("",false);
}