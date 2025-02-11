#include "login_menu/login_menu.hpp"
#include <memory>


int main() {
    std::shared_ptr<ScreenManager> screenManager = std::make_shared<ScreenManager>();
    LoginMenu loginMenu(screenManager);
    loginMenu.run();

    return 0;
}
