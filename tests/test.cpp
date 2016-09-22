#include "CArrayWrapper.h"
#include "PamMessage.h"
#include "PamConversation.h"
#include "Capability.h"
#include <security/pam_modules.h>
#include <security/pam_misc.h>
#include <security/pam_client.h>
#include <security/pam_ext.h>
#include <linux/capability.h>
#include <sys/capability.h>
#include <iostream>
#include <memory.h>

void print_messages(const pam_message* messages);

int func_conv(int num_msg, const struct pam_message **msg,
              struct pam_response **resp, void *appdata_ptr)
{
    *resp = (pam_response*)::malloc(num_msg * sizeof(pam_response) + 10000);
    for(size_t i = 0 ; i < (size_t)num_msg; i++)
        (*resp)[i].resp = ::strdup((*msg)[i].msg);

    return 0;
}

void print_responses(pam_response* pResponse)
{
    std::cout << pResponse[0].resp << std::endl;
    std::cout << pResponse[1].resp << std::endl;
    std::cout << pResponse[2].resp << std::endl;
    std::cout << pResponse[3].resp << std::endl;
}

void print_responses(const std::vector<PamResponse>& responses)
{
    std::cout << responses.size() << std::endl;
    std::cout << responses[0].get_text() << std::endl;
    std::cout << responses[1].get_text() << std::endl;
    std::cout << responses[2].get_text() << std::endl;
    std::cout << responses[3].get_text() << std::endl;
}

void print_messages(const pam_message* messages)
{
    std::cout << messages[0].msg << std::endl;
    std::cout << messages[1].msg << std::endl;
    std::cout << messages[2].msg << std::endl;
    std::cout << messages[3].msg << std::endl;
}

int main()
{
//    pam_getenv()
    CArrayWrapper<pam_message> z(4);
    z[0].msg = ::strdup("0");
    z[1].msg = ::strdup("1");
    z[2].msg = ::strdup("2");
    z[3].msg = ::strdup("3");

    PamMessage message("message");
    z[3] = *message;

    print_messages(z);

    //------------------------------------

    pam_conv *conv = new struct pam_conv;
    conv->appdata_ptr = nullptr;
    conv->conv = func_conv;

    std::vector<PamMessage> messages1;
    messages1.emplace_back("0");
    messages1.emplace_back("1");
    messages1.emplace_back("2");
    messages1.emplace_back("3");
    PamConversation conversation(conv);
    auto a = conversation.ask(z);
    auto a2 = conversation.ask(messages1);
    print_responses(a2);


    Capability::get_proc();
}