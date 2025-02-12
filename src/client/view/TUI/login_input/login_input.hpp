/**
 * @file login_input.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LoginInput class header file
 * @date 2025-02-12
 * 
 */

#ifndef LOGIN_INPUT_HPP
#define LOGIN_INPUT_HPP

#include "../screen_manager/screen_manager.hpp"
#include <string>

enum LoginInputStatus {
    SUCCESS,
    FAILURE
};

class LoginInput {
    private:
        ScreenManager * screenManager_;
        std::string title_;
        std::string username_;
        std::string password_;
        std::string message_;
        std::string instructons_;

    public:
        /*
        * @brief Construct a new Login Input object
        */
        LoginInput(ScreenManager *screenManager, std::string &title);

        /*
        * @brief Destroy the Login Input object
        */
        ~LoginInput() = default;

        /*
        * @brief Run the login input screen with all the components to enter the username and password for login and register
        *
        * @return LoginInputStatus the status of the login input
        */
        LoginInputStatus run();

        /*
        * @brief Get the Username
        *
        * @return std::string the username
        */
        std::string getUsername() const;

        /*
        * @brief Get the Password
        *
        * @return std::string the password
        */
        std::string getPassword() const;

        /*
        * @brief Add text under the input fields to show a message
        *
        * @param text the text to add
        */
        void addTextUnder(const std::string& text);

        /*
        * @brief Add instructions above the input fields to show a message (like a title or instructions)
        */
        void addInstructions(const std::string& instructions);
};


#endif // LOGIN_INPUT_HPP