#ifndef LOGIN_INPUT_HPP
#define LOGIN_INPUT_HPP

#include "screen_manager.hpp"
#include <memory>
#include <string>

class LoginInput {
    private:
        std::shared_ptr<ScreenManager> screenManager_;
        std::string title_;
        std::string username_;
        std::string password_;

    public:
        LoginInput(std::shared_ptr<ScreenManager> screenManager, std::string &title);

        ~LoginInput() = default;

        void run();

        std::string getUsername() const;

        std::string getPassword() const;
};


#endif // LOGIN_INPUT_HPP