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

/**
 * @brief Enum class to represent the state of the input
 * 
 */
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
        * @return InputState the state of the input
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
        std::string getUsername() const;

        /*
        * @brief Get the password
        *
        * @return string the password
        */
        std::string getPassword() const;
};

#endif // LOGIN_INPUT_HPP