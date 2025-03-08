#ifndef ILOGIN_MENU_HPP
#define ILOGIN_MENU_HPP

enum class LoginResult {
    SUCCESS,
    EXIT,
};

enum class Login {
    LOGGED,
    EXIT,
    NONE,
};

class ILogin_Menu {
  protected:
    virtual void createButtons() = 0;

    virtual void displayWindow() = 0;

  public:
    virtual ~ILogin_Menu() = default;

    virtual LoginResult render() = 0;
};

#endif