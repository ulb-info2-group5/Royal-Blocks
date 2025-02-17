/**
 * @file login_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class header file
 * @date 2025-02-12
 * 
 */

#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

enum class LoginState {
    LAUNCH_LOGIN,
    LAUNCH_REGISTER,
    EXIT,
    NONE,
};

/**
 * @brief LoginMenu class to show the login menu screen with choices to login or register
 * 
 */
class LoginMenu {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

    public:
        /*
        * @brief Construct a new Login Menu object
        */
        LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen);
        
        /*
        * @brief Destroy the Login Menu object
        */
        ~LoginMenu() = default;
        
        /*
        * @brief Render the login menu screen with all the components by asking the screen manager to render the components
        */
        LoginState render();
};

#endif // LOGIN_MENU_HPP