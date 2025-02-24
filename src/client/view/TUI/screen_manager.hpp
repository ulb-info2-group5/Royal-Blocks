#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "input/login_input.hpp"
#include "login_menu/login_menu.hpp"
#include "game_display/game_display.hpp"
#include "main_menu/main_menu.hpp"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <memory>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include "../dataExample.hpp"

constexpr char LOGIN_INPUT_TITLE[] = "Login";
constexpr char REGISTER_INPUT_TITLE[] = "Register";
constexpr std::string_view LOGIN_INSTRUCTIONS = "Please enter your username and password to login.";
constexpr std::string_view REGISTER_INSTRUCTIONS = "Please enter a username and a password to create an account.";
constexpr std::string_view LOGIN_MESSAGE = "Your account has been created successfully! You can now login.";

/**
 * @brief Enum class to represent the type of input to show to the user
 * 
 */
enum class InputType {
    LOGIN,
    REGISTER,
};

struct LoginInfo {
    std::string username;
    std::string password;
};

class ScreenManager {
    private:
        /*
        * @brief The screen to use to render the components in the terminal user interface
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_ = std::shared_ptr<ftxui::ScreenInteractive>(new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen()));

        /*
        * @brief The login menu to show to the user
        */
        LoginMenu loginMenu_ = LoginMenu(screen_);

        /*
        * @brief The login input to show to the user
        */
        LoginInput loginInput_ = LoginInput(screen_, LOGIN_INPUT_TITLE);

        /*
        * @brief The register input to show to the user
        */
        LoginInput registerInput_ = LoginInput(screen_, REGISTER_INPUT_TITLE);

        /*
        * @brief The main menu to show to the user
        */
        MainMenu mainMenu_ = MainMenu(screen_);

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
        * @brief Draw the start screen of the game with the title of the game
        */
        void drawStartScreen();

        /*
        * @brief Get the login info from the user
        */
        LoginInfo getLoginInfo();

        /*
        * @brief Get the register info from the user
        */
        LoginInfo getRegisterInfo();

        /*
        * @brief Run the login menu to show to the user
        */
        LoginState runLoginMenu();

        /*
        * @brief Run the login input to show to the user
        */
        InputState runLoginInput();

        /*
        * @brief Run the register input to show to the user
        */
        InputState runRegisterInput();

        /*
        * @brief Manage the main menu to show to the user with the choices to play a game, join a game, send messages to friends, etc
        */
        void manageMainMenu();

        /*
        * @brief Add a message to the login input to show to the user
        *
        * @param string message The message to show
        */
        void addMessageToLoginInput(const std::string_view message);

        /*
        * @brief Add a message to the register input to show to the user
        *
        * @param string message The message to show
        */
        void addMessageToRegisterInput(const std::string_view message);
};

#endif // SCREEN_MANAGER_HPP