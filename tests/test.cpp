#include "CArrayWrapper.h"
#include <security/pam_modules.h>
#include <iostream>
#include <memory.h>

void foo(pam_message** messages)
{
    std::cout << messages[0]->msg << std::endl;
    std::cout << messages[1]->msg << std::endl;
    std::cout << messages[2]->msg << std::endl;
    std::cout << messages[3]->msg << std::endl;
}


int main()
{
    CArrayWrapper<pam_message> z(5);
    z[0].msg = ::strdup("0");
    z[1].msg = ::strdup("1");
    z[2].msg = ::strdup("2");
    z[3].msg = ::strdup("3");

    foo(z);
}