#include "login_input.hpp"
#include "login_menu.hpp"
#include <memory>


int main() {
    std::shared_ptr<ScreenManager> screenManager = std::make_shared<ScreenManager>();
    std::shared_ptr<LoginInput> loginInput = std::make_shared<LoginInput>(screenManager);
    LoginMenu loginMenu(screenManager, loginInput);
    loginMenu.run();

    return 0;
}
