#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "input/login_input.hpp"
#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

constexpr std::string LOGIN_INPUT_TITLE = "Login";
constexpr std::string REGISTER_INPUT_TITLE = "Register";

enum class InputType {
    LOGIN,
    REGISTER,
};

class ScreenManager {
    private:
        /*
        * @brief The screen that will be used to show things to the terminal user interface (TUI)
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_ = std::shared_ptr<ftxui::ScreenInteractive>(new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen()));

        LoginMenu loginMenu_ = LoginMenu(screen_);

        LoginInput loginInput_ = LoginInput(screen_, LOGIN_INPUT_TITLE);

        LoginInput registerInput_ = LoginInput(screen_, REGISTER_INPUT_TITLE);

        MainMenu mainMenu_ = MainMenu(screen_);
        
        /*
        * @brief The current component to render on the screen
        */
        ftxui::Component component_;

        /*
        * @brief The exit status flag of the screen manager
        */
        bool exit_;

        /*
        * @brief Draw the start screen of the game with the title of the game
        */
        void drawStartScreen();

        void manageLoginMenu();

        void manageInputMenu(InputType type);

        void manageMainMenu();

    public:
        /*
        * @brief Construct a new Screen Manager object
        */
        ScreenManager();

        /*
        * @brief Destroy the Screen Manager object
        */
        ~ScreenManager() = default;

        /*
        * @brief Run the screen manager to display the components on the screen with the LoginMenu, MainMenu, etc
        */
        void run();
};

#endif // SCREEN_MANAGER_HPP