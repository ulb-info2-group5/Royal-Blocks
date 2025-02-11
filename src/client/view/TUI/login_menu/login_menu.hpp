#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP


#include "../UI/menu_ui.hpp"
#include <memory>

class LoginMenu : public MenuUi {
    private:
        
    public:
        LoginMenu(std::shared_ptr<ScreenManager> screenManager);
        ~LoginMenu() = default;

        void run() override;
};


#endif // LOGIN_MENU_HPP