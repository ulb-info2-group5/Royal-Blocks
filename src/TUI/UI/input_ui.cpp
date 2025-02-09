/**
 * @file input_ui.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Input UI definition file
 * @date 2025-02-09
 * 
 */

#include "input_ui.hpp"

InputUi::InputUi(std::string& content, const std::string& placeholder) {
    input_ = ftxui::Input(&content, placeholder);
}

ftxui::Component InputUi::GetComponent() const {
    return input_;
}