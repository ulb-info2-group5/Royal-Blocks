/**
 * @file button_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief ButtonUI declaration file
 * @date 2025-02-09
 *  
 */

#include "button_ui.hpp"

ButtonUi::ButtonUi(const std::string& label, std::function<void()> on_click) {
    button_ = ftxui::Button(label, on_click);
}

ftxui::Component ButtonUi::GetComponent() const {
    return button_;
}

