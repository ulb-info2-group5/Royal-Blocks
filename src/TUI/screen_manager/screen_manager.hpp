/**
* @file screen_manager.hpp
* @author Ethan Van Ruyskensvelde
* @brief ScreenManager class header file
* @date 2025-02-09
*
*/

#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

class ScreenManager {
    private:
        ftxui::ScreenInteractive screen;
        ftxui::Component mainComponent;

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
        * @brief Set the Component object
        *
        * @param component 
        */
        void SetComponent(const ftxui::Component component);
        
        /*
        * @brief Run the screen
        */
        void Run();
        
        /*
        * @brief Exit the screen
        */
        void Exit();
};

#endif // SCREEN_MANAGER_HPP