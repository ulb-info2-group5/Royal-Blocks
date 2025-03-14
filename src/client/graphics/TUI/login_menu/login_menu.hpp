/**
 * @file login_menu.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginMenu class header file
 * @date 2025-02-12
 *
 */

#ifndef LOGIN_MENU_HPP
#define LOGIN_MENU_HPP

#include <ftxui/component/component.hpp>
#include <string_view>

#include "../input/login_input.hpp"

enum class LoginResult {
    SUCCESS,
    EXIT,
};

enum class Login {
    LOGGED,
    EXIT,
    NONE,
};

constexpr char LOGIN_INPUT_TITLE[] = "Login";
constexpr char REGISTER_INPUT_TITLE[] = "Register";
constexpr std::string_view LOGIN_INSTRUCTIONS =
    "Please enter your username and password to login.";
constexpr std::string_view REGISTER_INSTRUCTIONS =
    "Please enter a username and a password to create an account.";
constexpr std::string_view LOGIN_MESSAGE =
    "Your account has been created successfully! You can now login.";

class Controller; // Forward declaration

/**
 * @brief LoginMenu class to show the login menu screen with choices to login or
 * register
 *
 */
class LoginMenu final {
  private:
    /*
     * @brief The screen to use to render the components
     */
    ScreenManager &screenManager_;

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

    void createButtons();

    void displayWindow();

  public:
    /*
     * @brief Construct a new Login Menu object
     *
     * @param screenManager The screen manager for asking to render the
     * components
     * @param controller The controller to interact with the server
     */
    LoginMenu(ScreenManager &screenManager, Controller &controller);

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

#endif // LOGIN_MENU_HPP
