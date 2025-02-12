/**
 * @file screen_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief ScreenManager class header file
 * @date 2025-02-12
 * 
 */

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
        void exitLoop();
        
        /*
        * @brief Exit the screen
        */
        void exit();

        /*
        * @brief Run the screen with all the components and the menus
        */
        void run();

};

#endif // SCREEN_MANAGER_HPP