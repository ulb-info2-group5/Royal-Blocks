#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <ftxui/component/screen_interactive.hpp>

class ScreenManager {
    private:
        ftxui::ScreenInteractive screen_;

    public:
        ScreenManager();
        
        ~ScreenManager();

        void loopScreen(const ftxui::Component component);

        void ExitLoopClosure();
        
        void Exit();

};

#endif // SCREEN_MANAGER_HPP