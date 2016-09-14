#ifndef PAMRESPONSE_H
#define PAMRESPONSE_H


#include <security/pam_modules.h>
#include <string>

class PamResponse : private pam_response
{
public:
    explicit PamResponse(const std::string& text = "");
    explicit PamResponse(const pam_response* response);
    PamResponse(const PamResponse& rhs);
    PamResponse& operator =(const PamResponse& rhs);
    PamResponse& operator =(const pam_response* response);

    ~PamResponse();

    std::string get_text() const;
    void set_text(const std::string& text);

    operator struct pam_response* ();
    operator const struct pam_response* () const;
};


#endif // PAMRESPONSE_H
