#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>

class ScreenManager {
    private:
        ftxui::ScreenInteractive screen_;

    public:
        /*
        * @brief Construct a new Screen Manager object
        */
        ScreenManager();

        /*
        * @brief Destroy the Screen Manager object
        */
        ~ScreenManager();

        /*
        * @brief Loop the screen with the given component
        */
        void loopScreen(const ftxui::Component &component);

        /*
        * @brief Exit the loop closure
        */
        void exitLoopClosure();
        
        /*
        * @brief Exit the screen
        */
        void exit();

};

#endif // SCREEN_MANAGER_HPP