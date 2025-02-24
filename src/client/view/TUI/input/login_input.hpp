/**
 * @file login_input.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class header file
 * @date 2025-02-12
 * 
 */

#ifndef LOGIN_INPUT_HPP
#define LOGIN_INPUT_HPP

#include <ftxui/component/screen_interactive.hpp>

#include <memory>
#include <string>
#include <string_view>

#include "../../ILogin_Input.hpp"

/**
 * @brief Enum class to represent the state of the input
 * 
 */
enum class InputState 
{
    SUBMIT,
    BACK,
    NONE,
};


/**
 * @brief LoginInput class to get the login input or register input from the user
 * 
 */
class LoginInput : public ILogin_Input
{
    private:
        /*
        * @brief The screen to use to render the components
        */
        std::shared_ptr<ftxui::ScreenInteractive> screen_;

        /*
        * @brief The title of the input screen (Login or Register)
        */
        std::string title_;

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

        InputState userState_;

        std::string msg_;

        ftxui::Component buttonSubmit_;
        ftxui::Component buttonBack_;
        ftxui::Component inputUsername_;
        ftxui::Component inputPassword_;
        ftxui::Component displayWindow_;

    protected:

        void displayButtonBack();

        void displayButtonSubmit(); 

        void displayWindow() override;

    public:
        /*
        * @brief Construct a new Login Input object
        *
        * @param screen The screen to use to render the components
        * @param title The title of the input screen (Login or Register)
        */
        LoginInput(std::shared_ptr<ftxui::ScreenInteractive> &screen, std::string title);

        /*
        * @brief Destroy the Login Input object
        */
        ~LoginInput() = default;

        /*
        * @brief Render the login input screen with all the components
        *
        */
        InputState render();

        /*
        * @brief Add an instruction to show to the user
        *
        * @param string instruction the instruction to show
        */
        void addInstruction(const std::string_view instruction);

        /*
        * @brief Add a message to show to the user
        *
        * @param string message the message to show
        */
        void addMessage(const std::string_view message);

        /*
        * @brief Get the username
        *
        * @return string the username
        */
        std::string getUsername() const override;

        /*
        * @brief Get the password
        *
        * @return string the password
        */
        std::string getPassword() const override;

        InputState getUserState() const;

        /*
        * @brief Clear the info of the user input (username and password)
        */
        void clearInfo();
};

#endif // LOGIN_INPUT_HPP