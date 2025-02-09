/**
 * @file menu_ui.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Menu UI definition file
 * @date 2025-02-09
 *
 */

#include "menu_ui.hpp"

MenuUi::MenuUi(const std::vector<std::string>& entries, int& selected) {
    menu_ = ftxui::Menu(&entries, &selected);
}

ftxui::Component MenuUi::GetComponent() const {
    return menu_;
}