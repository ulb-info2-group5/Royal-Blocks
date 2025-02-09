/**
 * @file text_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief TextUI class header file
 * @date 2025-02-09
 * 
 */

#ifndef TEXT_UI_HPP
#define TEXT_UI_HPP

#include <ftxui/component/component.hpp>
#include <string>

class TextUi {
    private:
        std::string text_;
        ftxui::Component textComponent_;

    public:
        /*
        * @brief Construct a new TextUi object
        *
        * @param texts The text to display
        */
        TextUi(const std::string& texts);
        
        /*
        * @brief Destroy the TextUi object
        */
        ~TextUi() = default;
        
        /*
        * @brief Get the Component object
        *
        * @return ftxui::Component The text component
        */
        ftxui::Component GetComponent() const;
};

#endif // TEXT_UI_HPP