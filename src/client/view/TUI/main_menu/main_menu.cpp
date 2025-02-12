/**
 * @file main_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief MainMenu class definition file
 * @date 2025-02-12
 * 
 */

#include "main_menu.hpp"

MainMenu::MainMenu(ScreenManager *screenManager) : MenuUi(screenManager, "Main Menu", std::vector<std::string>{"Play a game", "Join an invitation game", "Manage your profile", "Manage Friends List", "Send a message to a friend", "View the ranking"}) {}
