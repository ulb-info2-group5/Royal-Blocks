/**
 * @file input_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Input UI class header file
 * @date 2025-02-09
 * 
 */

#ifndef INPUT_UI_HPP
#define INPUT_UI_HPP

#include <ftxui/component/component.hpp>
#include <string>

class InputUi {
    private:
        ftxui::Component input_;
    
    public:
        /*
        * @brief Construct a new Input UI object
        *
        * @param content The content of the input
        * @param placeholder The placeholder of the input
        */
        InputUi(std::string& content, const std::string& placeholder);

        /*
        * @brief Destroy the Input UI object
        */
        ~InputUi() = default;

        /*
        * @brief Get the component of the input
        *
        * @return ftxui::Component The component of the input
        */
        ftxui::Component GetComponent() const;
};

#endif // INPUT_UI_HPP