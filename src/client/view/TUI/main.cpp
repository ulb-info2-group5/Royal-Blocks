#include "login_menu/login_menu.hpp"
#include <ftxui/component/component.hpp>
#include <memory>

int main() {
    std::shared_ptr<ftxui::ScreenInteractive> screen = std::shared_ptr<ftxui::ScreenInteractive>(
        new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen())
    );
    // TODO: add loginInput to the loginMenu
    LoginMenu loginMenu = LoginMenu(screen);
    loginMenu.render();
    return 0;
}
