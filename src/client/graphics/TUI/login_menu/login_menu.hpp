#ifndef TUI_LOGIN_MENU_HPP
#define TUI_LOGIN_MENU_HPP

#include <ftxui/component/component.hpp>

#include "../login_input/login_input.hpp"

class Controller;

namespace TUI {

    class MainTui;

    enum class LoginResult {
        SUCCESS,
        EXIT,
    };

    enum class Login {
        LOGGED,
        EXIT,
        NONE,
    };

    /**
     * @brief LoginMenu class to show the login menu screen with choices to
     * login or register
     *
     */
    class LoginMenu final {
      private:
        /*
         * @brief The screen to use to render the components
         */
        MainTui &mainTui_;

        /*
         * @brief The controller to ask for the data to show to the user
         */
        Controller &controller_;

        LoginInput loginInput_;

        LoginInput registerInput_;

        Login loginState_;

        LoginState userState_;

        ftxui::Component buttonRegister_;
        ftxui::Component buttonLogin_;
        ftxui::Component buttonExit_;

        ftxui::Component displayWindow_;

        /*
         * @brief Create the buttons needed for the login menu
         */
        void createButtons();

        /*
         * @brief Display the window of the login menu with all the components
         */
        void displayWindow();

      public:
        /*
         * @brief Construct a new Login Menu object
         *
         * @param screenManager The screen manager for asking to render the
         * components
         * @param controller The controller to interact with the server
         */
        LoginMenu(MainTui &screenManager, Controller &controller);

        /*
         * @brief Destroy the Login Menu object
         */
        ~LoginMenu() = default;

        /*
         * @brief Render the login menu screen with all the components
         *
         * @return LoginResult The result if login succeed or want to exit the
         * program
         */
        LoginResult render();
    };

} // namespace TUI

#endif // TUI_LOGIN_MENU_HPP
