#include "handle_ctrl.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

ftxui::Component handleCtrlC(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [](ftxui::Event event) {
        return event == ftxui::Event::Character('\x03'); // Ctrl+C event
    });
}

ftxui::Component handleCtrlZ(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [](ftxui::Event event) {
        return event == ftxui::Event::Character('\x1A'); // Ctrl+Z event
    });
}

ftxui::Component handleCtrl(ftxui::Component &component) {
    return ftxui::CatchEvent(component, [](ftxui::Event event) {
        return event == ftxui::Event::Character('\x1A') || event == ftxui::Event::Character('\x03'); // Ctrl+Z or Ctrl+C event
    });
}