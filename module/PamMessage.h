#ifndef PAMMESSAGE_H
#define PAMMESSAGE_H

#include <security/pam_modules.h>

#include <string>

class PamMessage : private pam_message
{
public:
    explicit PamMessage(const std::string& text = "");
    explicit PamMessage(const pam_message& message);
    PamMessage(const PamMessage& rhs);
    PamMessage& operator =(const PamMessage& rhs);
    PamMessage& operator =( const pam_message* message );
    ~PamMessage();

    std::string get_text() const;
    void set_text(const std::string& text);

    int get_style() const noexcept;
    void set_style(int style) noexcept;

    operator struct pam_message* ();
    operator const struct pam_message* () const;
};


#endif // PAMMESSAGE_H
