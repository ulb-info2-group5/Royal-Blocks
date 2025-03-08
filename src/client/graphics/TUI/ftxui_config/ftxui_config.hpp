#ifndef FTXUI_CONFIG_HPP
#define FTXUI_CONFIG_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>

/*
 * @brief Handle the Ctrl+C event to prevent the application from closing
 *
 * @param component The component to handle the Ctrl+C event
 * @return ftxui::Component The component with the Ctrl+C event handled
 */
ftxui::Component handleCtrlC(ftxui::Component &component);

/*
 * @brief Handle the Ctrl+Z event to prevent the application from closing
 *
 * @param component The component to handle the Ctrl+Z event
 * @return ftxui::Component The component with the Ctrl+Z event handled
 */
ftxui::Component handleCtrlZ(ftxui::Component &component);

/*
 * @brief Handle the Ctrl+C and Ctrl+Z event to prevent the application from
 * closing
 *
 * @param component The component to handle the Ctrl+C and Ctrl+Z event
 * @return ftxui::Component The component with the Ctrl+C and Ctrl+Z event
 * handled
 */
ftxui::Component handleCtrl(ftxui::Component &component);

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

