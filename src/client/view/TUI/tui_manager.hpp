/**
 * @file tui_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief TuiManager class declaration file
 * @date 2025-02-13
 * 
 */

#ifndef TUI_MANAGER_HPP
#define TUI_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>

#include "input/login_input.hpp"

/**
 * @brief TuiManager class is responsible for managing the terminal user interface
 * 
 */
class TuiManager {
    private:
        /*
        * @brief The screen object that will be used to render the terminal user interface
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

         /*
        * @brief LoginInput object to get the login input
        */
        std::shared_ptr<LoginInput> loginInput_;

        /*
        * @brief LoginInput object to get the register input
        */
        std::shared_ptr<LoginInput> registerInput_;

        /*
         * @brief A start screen to display when the TuiManager is first run
         */
        void startScreen();

    public:
        /*
         * @brief Construct a new Tui Manager object
         */
        TuiManager();

        /*
         * @brief Destroy the Tui Manager object
         */
        ~TuiManager() = default;

        /*
         * @brief Run the terminal user interface
         */
        void run();

        /*
         * @brief Get the username from the login/register input
         * 
         * @return std::string the username
         */
        std::string getUserName() const;

        /*
         * @brief Get the password from the login/register input
         * 
         * @return std::string the password
         */
        std::string getPassword() const;
};

#endif // TUI_MANAGER_HPP