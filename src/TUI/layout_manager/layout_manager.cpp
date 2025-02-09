/**
 * @file layout_manager.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief LayoutManager definition file
 * @date 2025-02-09
 * 
 */

#include "layout_manager.hpp"

LayoutManager::LayoutManager(std::vector<ftxui::Component> components) {
    layout_ = ftxui::Container::Vertical(components);
}

ftxui::Component LayoutManager::GetComponent() const {
    return layout_;
}