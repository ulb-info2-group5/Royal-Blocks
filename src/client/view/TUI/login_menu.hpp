#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP


#include "menu_ui.hpp"
#include "login_input.hpp"

class LoginMenu : public MenuUi {
    private:
        std::shared_ptr<LoginInput> loginInput_;
    public:
        LoginMenu(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<LoginInput> loginInput);
        ~LoginMenu() = default;

        void run() override;
};


#endif // LOGIN_MENU_HPP