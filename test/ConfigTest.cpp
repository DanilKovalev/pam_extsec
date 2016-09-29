#include "ConfigTest.h"

#include "ConfigFile.h"

void ConfigTest::check_open()
{
    ConfigFile file("content/config.json");

    CPPUNIT_ASSERT_THROW(ConfigFile("no_file"), std::exception );
    CPPUNIT_ASSERT_THROW(ConfigFile("content/bad_config.json"), std::exception );
}

void ConfigTest::check_parse()
{
    ConfigFile file("content/config.json");
    CPPUNIT_ASSERT(file.get_config("tty1").capability.size() == 2);
    CPPUNIT_ASSERT(file.get_config("tty2").syscalls.size() == 1);
}
