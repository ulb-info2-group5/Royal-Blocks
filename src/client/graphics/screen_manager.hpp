#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "GUI/main_gui.hpp"
#include "TUI/main_tui.hpp"

#include <QApplication>
#include <memory>

class Controller; // Forward declaration

enum class UiChoice; // Forward declaration

class ScreenManager {
  private:
    /*
     *
     */
    Controller &controller_;

    UiChoice uiChoice_;

    std::unique_ptr<MainTui> tui_;

    std::unique_ptr<QApplication> app_;

    std::unique_ptr<MainGui> gui_;

  public:
    /*
     * @brief Construct a new Screen Manager object
     *
     * @param controller The controller to ask for the data to show to the user
     */
    ScreenManager(Controller &controller, UiChoice uiChoice,
                  std::pair<int, char **> args);

    /*
     * @brief Destroy the Screen Manager object
     */
    ~ScreenManager() = default;

    /*
     * @brief Run the screen manager to manage the screens to show to the user
     *
     * @return The exit code of the program of the tui or gui
     */
    int run();

    void forceRefresh();
};

#endif // SCREEN_MANAGER_HPP
