/**
 * @file button_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief ButtonUI class header file
 * @date 2025-02-09
 *  
 */

#ifndef BUTTON_UI_HPP
#define BUTTON_UI_HPP

#include <ftxui/component/component.hpp>
#include <string>

class ButtonUi {
    private:
        ftxui::Component button_;

    public:
        /*
        * @brief Construct a new ButtonUi object
        *
        * @param label The label of the button
        * @param on_click The function to call when the button is clicked
        */
        ButtonUi(const std::string& label, std::function<void()> on_click);

        /*
        * @brief Destroy the ButtonUi object
        */
        ~ButtonUi() = default;
        
        /*
        * @brief Get the Component object
        *
        * @return ftxui::Component The button component
        */
        ftxui::Component GetComponent() const;
    
};


#endif // BUTTON_UI_HPP