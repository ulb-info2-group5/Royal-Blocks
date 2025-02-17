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


enum class InputState {
    DONE,
    BACK,
    NONE,
};


/**
 * @brief LoginInput class to get the login input or register input from the user
 * 
 */
class LoginInput {
    private:
        std::shared_ptr<ftxui::ScreenInteractive> screen_;
        std::string title_;
        std::string username_;
        std::string password_;
        std::string instruction_;
        std::string message_;

    public:
        /*
        * @brief Construct a new Login Input object
        */
        LoginInput(std::shared_ptr<ftxui::ScreenInteractive> &screen, std::string title);

        /*
        * @brief Destroy the Login Input object
        */
        ~LoginInput() = default;

        /*
        * @brief Render the login input screen with all the components by askig ScreenManager to render the components
        *
        */
        InputState render();

        /*
        * @brief Add an instruction to show to the user
        *
        * @param string instruction the instruction to show
        */
        void addInstruction(std::string &instruction);

        /*
        * @brief Add a message to show to the user
        *
        * @param string message the message to show
        */
        void addMessage(std::string &message);

        /*
        * @brief Get the username
        *
        * @return string the username
        */
        std::string getUsername() const;

        /*
        * @brief Get the password
        *
        * @return string the password
        */
        std::string getPassword() const;
};

#endif // LOGIN_INPUT_HPP