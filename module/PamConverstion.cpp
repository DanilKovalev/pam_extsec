#include "PamConverstion.h"

PamConverstion::PamConverstion(struct pam_conv *conv)
: m_conv(conv)
{
}

