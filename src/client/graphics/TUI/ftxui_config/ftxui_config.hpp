#ifndef FTXUI_CONFIG_HPP
#define FTXUI_CONFIG_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>

/*
 * @brief Global style for the buttons
 * 
 * @return ftxui::ButtonOption The global style for the buttons 
 */
ftxui::ButtonOption GlobalButtonStyle();

/*
 * @brief Input option for a password input
 * 
 * @return ftxui::InputOption The input option for a password input
 */
ftxui::InputOption PasswordInputOption();

#endif // FTXUI_CONFIG_HPP

