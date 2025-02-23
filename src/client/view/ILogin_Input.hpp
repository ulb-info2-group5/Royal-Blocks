#ifndef ILOGIN_INPUT_HPP
#define ILOGIN_INPUT_HPP

#include <string>

class ILogin_Input
{
    protected : 

    virtual void displayWindow() = 0;

    public : 

    virtual ~ILogin_Input() = default;

    virtual std::string getPassword() const = 0;

    virtual std::string getUsername() const = 0;
};

#endif