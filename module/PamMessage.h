#ifndef PAMMESSAGE_H
#define PAMMESSAGE_H

#include <security/pam_modules.h>

#include <string>

class PamMessage
{
public:
    explicit PamMessage(const std::string& text);
    PamMessage(const PamMessage& rhs);
    PamMessage& operator =(const PamMessage& rhs);
    ~PamMessage();

    std::string get_text() const;
    void set_text(const std::string& text);

    int get_style() const noexcept;
    void set_style(int style) noexcept;

    operator struct pam_message& ();
    operator const struct pam_message& () const;

private:
    void free_message() noexcept;

private:
    struct pam_message m_message;
};


#endif // PAMMESSAGE_H
