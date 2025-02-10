#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP


#include <ftxui/component/screen_interactive.hpp>

class ScreenManager {
    private:
        ftxui::ScreenInteractive screen_;

    public:
        ScreenManager();
        ~ScreenManager() = default;

        void loopScreen(const ftxui::Component component);

        void ExitLoopClosure();
        

};

#endif // SCREEN_MANAGER_HPP