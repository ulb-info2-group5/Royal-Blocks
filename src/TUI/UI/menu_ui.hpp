/**
 * @file menu_ui.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief Menu UI class header file
 * @date 2025-02-09
 *
 */

#ifndef MENU_UI_HPP
#define MENU_UI_HPP

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

class MenuUi {
    private:
        ftxui::Component menu_;

    public:
        /*
        * @brief Construct a new Menu Ui object
        *
        * @param entries The entries to display in the menu
        * @param selected The selected entry
        */
        MenuUi(const std::vector<std::string>& entries, int& selected);

        /*
        * @brief Destroy the Menu Ui object
        */
        ~MenuUi() = default; 

        /*
        * @brief Get the Component object
        *
        * @return ftxui::Component 
        */
        ftxui::Component GetComponent() const;

    };

#endif // MENU_UI_HPP