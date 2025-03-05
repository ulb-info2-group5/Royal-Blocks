#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "login_menu/login_menu.hpp"
#include "main_menu/main_menu.hpp"

#include <boost/asio/detail/std_fenced_block.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

class Controller; // Forward declaration

class ScreenManager {
  private:
    /*
     *
     */
    Controller *controller_;

    /*
     * @brief The screen to use to render the components in the terminal user
     * interface
     */
    ftxui::ScreenInteractive screen_;

    /*
     * @brief The login menu to show to the user
     */
    LoginMenu loginMenu_;

    /*
     * @brief The main menu to show to the user
     */
    MainMenu mainMenu_;

    /*
     * @brief Draw the start screen of the game with the title of the game
     */
    void drawStartScreen();

    /*
     * @brief Draw the end screen of the game with a goodbye message
     */
    void drawEndScreen();

  public:
    /*
     * @brief Construct a new Screen Manager object
     *
     * @param controller The controller to ask for the data to show to the user
     */
    ScreenManager(Controller *controller);

    /*
     * @brief Destroy the Screen Manager object
     */
    ~ScreenManager();

    /*
     * @brief Run the screen manager to manage the screens to show to the user
     */
    void run();
};

#endif // SCREEN_MANAGER_HPP