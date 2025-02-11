#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP


#include "menu_ui.hpp"
#include "login_input.hpp"
#include "screen_manager.hpp"
#include <memory>

class LoginMenu : public MenuUi {
    private:
        
    public:
        LoginMenu(std::shared_ptr<ScreenManager> screenManager);
        ~LoginMenu() = default;

        void run() override;
};


#endif // LOGIN_MENU_HPP