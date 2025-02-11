#ifndef LOGIN_INPUT_HPP
#define LOGIN_INPUT_HPP

#include "../screen_manager/screen_manager.hpp"
#include <memory>
#include <string>

enum LoginInputStatus {
    SUCCESS,
    FAILURE
};

class LoginInput {
    private:
        std::shared_ptr<ScreenManager> screenManager_;
        std::string title_;
        std::string username_;
        std::string password_;
        std::string message_;
        std::string instructons_;

    public:
        LoginInput(std::shared_ptr<ScreenManager> screenManager, std::string &title);

        ~LoginInput() = default;

        LoginInputStatus run();

        std::string getUsername() const;

        std::string getPassword() const;

        void addTextUnder(const std::string& text);

        void addInstructions(const std::string& instructions);
};


#endif // LOGIN_INPUT_HPP