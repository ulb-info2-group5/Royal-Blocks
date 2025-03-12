#ifndef FTXUI_CONFIG_HPP
#define FTXUI_CONFIG_HPP

#include <ftxui/component/component.hpp>
#include <string_view>

// Constants for the TUI
constexpr std::string_view 
    STR_BACK_TO_MAIN_MENU = "Back to main menu",
    STR_ADD = "Add",
    STR_ADD_A_FRIEND = "Add a friend",
    STR_REMOVE_A_FRIEND = "Remove a friend",
    STR_BACK = "Back",
    STR_NAME_OF_FRIEND = "Name of friend",
    STR_NO = "No",
    STR_YES = "Yes",
    STR_NO_FRIEND = "You don't have friends yet",
    STR_FRIENDS_LIST = "Friends list",
    STR_FRIENDS = "Your friends",
    STR_QUIT_GAME = "Quit Game",
    STR_ENDLESS = "Endless",
    STR_DUAL = "Dual",
    STR_CLASSIC = "Classic",
    STR_ROYAL = "Royal",
    STR_SELECT_MOD = "Select a game mode",
    STR_JOIN_FRIEND = "Join a friend",
    STR_JOIN_RANDOM = "Join a random game",
    STR_WAITING_FRIEND = "Waiting for the friend to start the game",
    STR_WAIT = "Please wait ...",
    STR_JOIN_FRIEND_OR_RANDOM = "Join a friend or a random game",
    STR_SELECT_FRIEND_TO_JOIN = "Select a friend to join",
    STR_CONFIRM = "Confirm",
    STR_SELECT_NUM_PLAYERS = "Select the number of players",
    STR_ENTER_USERNAME = "Enter username",
    STR_ENTER_PASSWORD = "Enter password",
    STR_SUBMIT = "Submit",
    STR_REGISTRATION_FAILED = "Registration failed! Try again.",
    STR_INCORRECT = "Incorrect username or password!",
    STR_REGISTER = "Register",
    STR_LOGIN = "Login",
    STR_EXIT = "Exit",
    STR_LOGIN_MENU = "Login Menu",
    STR_INSTRUCTION_LOGIN = "Please login to your account or create one to enter the game",
    STR_OK = "OK",
    STR_CREATE_GAME = "▶ Create a game",
    STR_JOIN_GAME = "▶ Join a game",
    STR_MESSAGES = "💬 Messages",
    STR_RANKING = "🏆 Ranking",
    STR_PROFILE = "Profile",
    STR_MANAGE_FRIENDS_LIST = "👥 Manage friends list",
    STR_MANAGE_PROFILE = "⚙ Manage profile",
    STR_MAIN_MENU = "🎮 Main Menu 🎮",
    STR_WELCOME = "Welcome to the game menu of Tetris Royal !",
    STR_SCORE = "Score",
    STR_USER = "User",
    STR_ENDLESS_RANKING = "Endless mod Ranking",
    STR_NEW_PASSWORD = "New password",
    STR_NEW_USERNAME = "New username",
    STR_PROFILE_MANAGER = "Profile Manager",
    STR_CHANGE_INFO = "You can change your username and password here",
    STR_SEND = "Send",
    STR_WRITE_MESSAGE = "Write a message...",
    STR_NO_CONVERSATION = "No conversation",
    STR_FRIENDS_LIST_TITLE = " --- FRIENDS LIST --- ",
    STR_CONVERSATION_TITLE = " --- CONVERSATION --- ",
    STR_ADD_FRIEND_TITLE = "-- Add a friend --";
    

const ftxui::Element WELCOME_TITLE = ftxui::vbox({
    ftxui::text(
        R"(__          __  _                            _          _____                   _   _______   _        _       _ )"),
    ftxui::text(
        R"(\ \        / / | |                          | |        |  __ \                 | | |__   __| | |      (_)     | |)"),
    ftxui::text(
        R"( \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |__) |___  _   _  __ _| |    | | ___| |_ _ __ _ ___  | |)"),
    ftxui::text(
        R"(  \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  |  _  // _ \| | | |/ _` | |    | |/ _ \ __| '__| / __| | |)"),
    ftxui::text(
        R"(   \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | \ \ (_) | |_| | (_| | |    | |  __/ |_| |  | \__ \ |_|)"),
    ftxui::text(
        R"(    \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  |_|  \_\___/ \__, |\__,_|_|    |_|\___|\__|_|  |_|___/ (_))"),
    ftxui::text(
        R"(                                                                     __/ |                                       )"),
    ftxui::text(
        R"(                                                                    |___/                                        )"),
});

const ftxui::Element GOODBYE_TITLE = ftxui::vbox({
    ftxui::text(
        R"(  ______                 _ _                    _ )"),
    ftxui::text(
        R"( / _____)               | | |                  | |)"),
    ftxui::text(
        R"(| /  ___  ___   ___   _ | | | _  _   _  ____   | |)"),
    ftxui::text(
        R"(| | (___)/ _ \ / _ \ / || | || \| | | |/ _  )  |_|)"),
    ftxui::text(
        R"(| \____/| |_| | |_| ( (_| | |_) ) |_| ( (/ /    _ )"),
    ftxui::text(
        R"( \_____/ \___/ \___/ \____|____/ \__  |\____)  |_|)"),
    ftxui::text(
        R"(                                (____/            )"),
});

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

