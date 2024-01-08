#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>

class ñredentials {
public:
    ñredentials (const std::string& filename);
    std::string getUsername() const;
    std::string getPassword() const;

private:
    std::string username;
    std::string password;
};

#endif // CREDENTIALS_H
