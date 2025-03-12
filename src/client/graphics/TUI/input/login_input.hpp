/**
 * @file login_input.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class header file
 * @date 2025-02-12
 *
 */

#ifndef LOGIN_INPUT_HPP
#define LOGIN_INPUT_HPP

#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>
#include <string_view>

#include "../../ILogin_Input.hpp"

class Controller; // Forward declaration

class ScreenManager; // Forward declaration

/**
 * @brief LoginInput class to get the login input or register input from the
 * user
 *
 */
class LoginInput : public ILogin_Input {
  private:
    /*
     * @brief The screen to use to render the components
     */
     ScreenManager &screenManager_;

    /*
     * @brief The controller to ask for the data to show to the user
     */
    Controller &controller_;

    /*
     * @brief The title of the input screen (Login or Register)
     */
    std::string title_;

    /*
     * @brief The type of the login (Login or Register)
     */
    LoginType loginType_;

    /*
     * @brief The state of the login input
     */
    LoginState loginState_;

    /*
     * @brief The username of the user
     */
    std::string username_;

    /*
     * @brief The password of the user
     */
    std::string password_;

    /*
     * @brief The instruction to show to the user
     */
    std::string instruction_;

    /*
     * @brief The custom message to show to the user
     */
    std::string message_;

    std::string msg_;

    ftxui::Component buttonSubmit_;
    ftxui::Component buttonBack_;
    ftxui::Component inputUsername_;
    ftxui::Component inputPassword_;
    ftxui::Component displayWindow_;

  protected:
    void createButtonBack() override;

    void createButtonSubmit() override;

    void displayWindow() override;

  public:
    /*
     * @brief Construct a new Login Input object
     *
     * @param screen The screen to use to render the components
     * @param title The title of the input screen (Login or Register)
     */
    LoginInput(ScreenManager &screenManager, Controller &controller,
               std::string title, LoginType loginType);

    /*
     * @brief Destroy the Login Input object
     */
    ~LoginInput() = default;

    /*
     * @brief Render the login input screen with all the components
     */
    LoginState render() override;

    /*
     * @brief Add an instruction to show to the user
     *
     * @param string instruction the instruction to show
     */
    void addInstruction(const std::string_view instruction) override;

    /*
     * @brief Add a message to show to the user
     *
     * @param string message the message to show
     */
    void addMessage(const std::string_view message) override;

    /*
     * @brief Clear the info of the user input (username and password)
     */
    void clearInfo() override;
};

#endif // LOGIN_INPUT_HPP
