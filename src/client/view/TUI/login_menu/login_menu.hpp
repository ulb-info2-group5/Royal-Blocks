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

/**
 * @brief LoginMenu class to show the login menu screen with choices to login or register
 * 
 */
class LoginMenu {
    private:
        /*
        * @brief ScreenInteractive to render the menu
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

        /*
        * @brief LoginInput object to render the login input
        */
        std::shared_ptr<LoginInput> loginInput_;

        /*
        * @brief LoginInput object to render the register input
        */
        std::shared_ptr<LoginInput> registerInput_;

    public:
        /*
        * @brief Construct a new Login Menu object
        */
        LoginMenu(std::shared_ptr<ftxui::ScreenInteractive> screen, std::shared_ptr<LoginInput> loginInput, std::shared_ptr<LoginInput> registerInput);
        
        /*
        * @brief Destroy the Login Menu object
        */
        ~LoginMenu() = default;
        
        /*
        * @brief Render the login menu screen with all the components
        */
        void render();
};


#endif // LOGIN_MENU_HPP