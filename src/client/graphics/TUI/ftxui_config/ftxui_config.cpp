#include "ftxui_config.hpp"

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
        return event == ftxui::Event::Character('\x1A')
               || event
                      == ftxui::Event::Character(
                          '\x03'); // Ctrl+Z or Ctrl+C event
    });
}

ftxui::ButtonOption GlobalButtonStyle() {
    ftxui::ButtonOption buttonStyle;
    buttonStyle.transform = [](const ftxui::EntryState& state) {
        return ftxui::hbox({
                   ftxui::filler(),
                   ftxui::text(state.label) | ftxui::center,
                   ftxui::filler()
               }) 
            | ftxui::xflex
            | (state.active ? ftxui::color(ftxui::Color::Yellow) : ftxui::color(ftxui::Color::White)) 
            | (state.focused ? ftxui::borderDouble : ftxui::border);
    };
    return buttonStyle;
}

ftxui::InputOption PasswordInputOption() {
    ftxui::InputOption passwordOption;
    passwordOption.password = true;
    return passwordOption;
}