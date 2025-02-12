/**
 * @file login_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class header file
 * @date 2025-02-12
 * 
 */
 
#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP

#include "../UI/menu_ui.hpp"
#include <memory>

class LoginMenu : public MenuUi {
    public:
        /*
        * @brief Construct a new Login Menu object
        */
        LoginMenu(std::shared_ptr<ScreenManager> screenManager);
        
        /*
        * @brief Destroy the Login Menu object
        */
        ~LoginMenu() = default;
        
        /*
        * @brief Run the login menu screen with all the components
        */
        void run() override;
};


#endif // LOGIN_MENU_HPP