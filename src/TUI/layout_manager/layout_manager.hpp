/**
 * @file layout_manager.hpp
 * @author Ethan Van Ruyskensvelde
 * @brief LayoutManager class header file
 * @date 2025-02-09
 * 
 */

#ifndef LAYOUT_MANAGER_HPP
#define LAYOUT_MANAGER_HPP

#include <ftxui/component/component.hpp>

class LayoutManager {
    private:
        ftxui::Component layout_;

    public:
        /*
        * @brief Construct a new Layout Manager object
        *
        * @param components A vector of components to be added to the layout
        */
        LayoutManager(std::vector<ftxui::Component> components);

        /*
        * @brief Destroy the Layout Manager object
        */
        ~LayoutManager() = default;

        /*
        * @brief Get the layout component
        *
        * @return ftxui::Component The layout component
        */
        ftxui::Component GetComponent() const;
};

#endif // LAYOUT_MANAGER_HPP