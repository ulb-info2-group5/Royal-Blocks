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

#include "../../ILogin_Menu.hpp"

/**
 * @brief Enum class to represent the state of the login menu
 * 
 */
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
class LoginMenu : public ILogin_Menu
{
    private:
        /*
        * @brief The screen to use to render the components
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

        LoginState userState_;

        ftxui::Component buttonRegister_;
        ftxui::Component buttonLogin_;
        ftxui::Component buttonExit_;
        // ftxui::Component buttonDisplay_;

        ftxui::Component displayWindow_;

    protected:

        void displayButtons() override;

        void displayWindow() override;

    public:
        /*
        * @brief Construct a new Login Menu object
        *
        * @param screen The screen to use to render the components
        */
        LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen);
        
        /*
        * @brief Destroy the Login Menu object
        */
        ~LoginMenu() = default;
        
        /*
        * @brief Render the login menu screen with all the components
        *
        * @return LoginState The state of the login menu
        */
        LoginState render();
};

#endif // LOGIN_MENU_HPP