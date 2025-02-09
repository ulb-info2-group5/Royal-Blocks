/**
 * @file text_ui.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief TextUI declaration file
 * @date 2025-02-09
 * 
 */

#include "text_ui.hpp"

TextUi::TextUi(const std::string& texts) : text_(texts), textComponent_(ftxui::Renderer([this] { return ftxui::text(text_) | ftxui::center; })) {}

ftxui::Component TextUi::GetComponent() const {
    return textComponent_;
}