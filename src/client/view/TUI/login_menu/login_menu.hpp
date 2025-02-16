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

#include "../input/login_input.hpp"

enum class LoginOption {
    REGISTER_SUCCESS,
    LOGIN_SUCCESS,
    NONE,
};

/**
 * @brief LoginMenu class to show the login menu screen with choices to login or register
 * 
 */
class LoginMenu {
    private:
        ScreenManager *screenManager_;
        LoginOption option_;
        bool exit_ = false;
        LoginInput loginInput_;
        LoginInput registerInput_;

        void checkOption();

    public:
        /*
        * @brief Construct a new Login Menu object
        */
        LoginMenu(ScreenManager *screenManager, LoginOption option = LoginOption::NONE);
        
        /*
        * @brief Destroy the Login Menu object
        */
        ~LoginMenu() = default;
        
        /*
        * @brief Render the login menu screen with all the components by asking the screen manager to render the components
        */
        void render();

        /*
        * @brief Add an option to the login menu to know what to do after the login/register process.
        * It's used to know if we have to add a message to the screen after the login/register process depending on the login/register input.
        *
        * @param option The option to add to the login menu
        */
        void addOption(const LoginOption option);
};

#endif // LOGIN_MENU_HPP