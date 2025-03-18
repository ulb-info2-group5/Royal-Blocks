#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "TUI/main_tui.hpp"

class Controller; // Forward declaration

enum class UiChoice; // Forward declaration

class ScreenManager {
  private:
    /*
     *
     */
    Controller &controller_;

    UiChoice uiChoice_;

    MainTui tui_;

  public:
    /*
     * @brief Construct a new Screen Manager object
     *
     * @param controller The controller to ask for the data to show to the user
     */
    ScreenManager(Controller &controller, UiChoice uiChoice);

    /*
     * @brief Destroy the Screen Manager object
     */
    ~ScreenManager() = default;

    /*
     * @brief Run the screen manager to manage the screens to show to the user
     */
    void run();

    void forceRefresh();
};

#endif // SCREEN_MANAGER_HPP