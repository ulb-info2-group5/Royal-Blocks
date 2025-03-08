#ifndef ILOGIN_INPUT_HPP
#define ILOGIN_INPUT_HPP

#include <string_view>

enum class LoginType {
    LOGIN,
    REGISTER,
    NONE,
};

enum class LoginState {
    SUBMIT,
    BACK,
    NONE,
};

class ILogin_Input {
  protected:
    virtual void createButtonBack() = 0;

    virtual void createButtonSubmit() = 0;

    virtual void displayWindow() = 0;

  public:
    virtual ~ILogin_Input() = default;

    virtual LoginState render() = 0;

    virtual void addInstruction(const std::string_view instruction) = 0;

    virtual void addMessage(const std::string_view message) = 0;

    virtual void clearInfo() = 0;
};

#endif