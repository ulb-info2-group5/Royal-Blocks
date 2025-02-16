#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

class ScreenManager {
    private:
        /*
        * @brief The screen that will be used to show things to the terminal user interface (TUI)
        */
        ftxui::ScreenInteractive screen_;

        /*
        * @brief The current component to render on the screen
        */
        ftxui::Component component_;

        /*
        * @brief The exit status flag of the screen manager
        */
        bool exit_;

        /*
        * @brief Draw the start screen of the game with the title of the game
        */
        void drawStartScreen();

    public:
        /*
        * @brief Construct a new Screen Manager object
        */
        ScreenManager();

        /*
        * @brief Destroy the Screen Manager object
        */
        ~ScreenManager() = default;

        /*
        * @brief Run the screen manager to display the components on the screen with the LoginMenu, MainMenu, etc
        */
        void run();
    
        /*
        * @brief Render the component on the screen
        *
        * @param component The component to render on the screen
        */
        void renderComponent(const ftxui::Component &component);

        /*
        * @brief Render the component on the screen without exiting the previous loop
        *
        * @param component The component to render on the screen
        */
        void renderComponentNoExitLoop(const ftxui::Component &component);

        /*
        * @brief Exit the screen manager and close the screen
        */
        void exit();

        /*
        * @brief Exit the current loop of the screen manager
        */
        void exitLoop();
};

#endif // SCREEN_MANAGER_HPP