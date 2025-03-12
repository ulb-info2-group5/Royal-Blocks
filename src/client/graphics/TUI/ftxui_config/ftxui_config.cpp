#include "ftxui_config.hpp"

ftxui::ButtonOption GlobalButtonStyle() {
    ftxui::ButtonOption buttonStyle;
    buttonStyle.transform = [](const ftxui::EntryState& state) {
        return ftxui::hbox({
                   ftxui::filler(),
                   ftxui::text(state.label) | ftxui::center | ftxui::bold,
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
