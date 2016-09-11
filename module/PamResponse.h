#ifndef PAMRESPONSE_H
#define PAMRESPONSE_H


#include <security/pam_modules.h>
#include <string>

class PamResponse
{
public:
    explicit PamResponse(const std::string& text = "");
    explicit PamResponse(struct pam_response* response);
    PamResponse(const PamResponse& rhs);
    PamResponse& operator =(const PamResponse& rhs);

    ~PamResponse();

    std::string get_text() const;
    void set_text(const std::string& text);

    operator struct pam_response& ();
    operator const struct pam_response& () const;

private:
    static void free_responce(pam_response& response ) noexcept ;

private:
    struct pam_response m_response;
};


#endif // PAMRESPONSE_H
