#ifndef TUI_FTXUI_CONFIG_HPP
#define TUI_FTXUI_CONFIG_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string_view>

namespace TUI {

    // Constants for the TUI
    inline constexpr std::string_view
        STR_BACK_TO_MAIN_MENU = "Back to main menu",
        STR_ADD = "Add", STR_ADD_A_FRIEND = "Add a friend",
        STR_REMOVE_A_FRIEND = "Remove a friend", STR_BACK = "Back",
        STR_CANCEL = "Cancel", STR_NAME_OF_FRIEND = "Name of friend",
        STR_NO = "No", STR_YES = "Yes",
        STR_NO_FRIEND = "You don't have friends yet",
        STR_FRIENDS_LIST = "Friends list", STR_FRIENDS = "Your friends",
        STR_QUIT_GAME = "Quit Game", STR_ENDLESS = "Endless", STR_DUAL = "Dual",
        STR_CLASSIC = "Classic", STR_ROYAL = "Royal",
        STR_SELECT_MOD = "Select a game mode",
        STR_JOIN_FRIEND = "Join a friend",
        STR_JOIN_RANDOM = "Join a random game",
        STR_SPECTATE_FRIEND = "Spectate a friend",
        STR_WAITING_FRIEND = "Waiting for the friend to start the game",
        STR_WAIT = "Please wait ...",
        STR_JOIN_FRIEND_OR_RANDOM = "Join a friend or a random game",
        STR_SELECT_FRIEND_TO_JOIN = "Select a friend to join",
        STR_CONFIRM = "Confirm",
        STR_SELECT_NUM_PLAYERS = "Select the number of players",
        STR_ENTER_USERNAME = "Enter username",
        STR_ENTER_PASSWORD = "Enter password", STR_SUBMIT = "Submit",
        STR_REGISTRATION_FAILED = "Registration failed! Try again.",
        STR_INCORRECT = "Authentication failed !", STR_REGISTER = "Register",
        STR_LOGIN = "Login", STR_EXIT = "Exit", STR_LOGIN_MENU = "Login Menu",
        STR_INSTRUCTION_LOGIN =
            "Please login to your account or create one to enter the game",
        STR_OK = "OK", STR_CREATE_GAME = "▶ Create a game",
        STR_JOIN_GAME = "▶ Join a game", STR_MESSAGES = "💬 Messages",
        STR_RANKING = "🏆 Ranking", STR_PROFILE = "Profile",
        STR_MANAGE_FRIENDS_LIST = "👥 Manage friends list",
        STR_MANAGE_PROFILE = "⚙ Manage profile",
        STR_MAIN_MENU = "🎮 Main Menu 🎮",
        STR_WELCOME = "Welcome to the main menu of Tetris Royal !",
        STR_SCORE = "Score", STR_USER = "User",
        STR_ENDLESS_RANKING = "Endless mod Ranking",
        STR_NEW_PASSWORD = "New password", STR_NEW_USERNAME = "New username",
        STR_PROFILE_MANAGER = "Profile Manager",
        STR_CHANGE_INFO = "You can change your username and password here",
        STR_SEND = "Send", STR_WRITE_MESSAGE = "Write a message...",
        STR_NO_CONVERSATION = "No conversation",
        STR_FRIENDS_LIST_TITLE = " --- FRIENDS LIST --- ",
        STR_CONVERSATION_TITLE = " --- CONVERSATION --- ",
        STR_ADD_FRIEND_TITLE = "-- Add a friend --",
        STR_MANAGE_FRIENDS_REQUESTS = "Manage friends requests",
        STR_NO_FRIEND_REQUEST = "You don't have any friend request",
        STR_RETURN_TO_MAIN_MENU = "Return to main menu",
        STR_PLAYER_DEAD = " ☠️ ", LOGIN_INPUT_TITLE = "Login",
        REGISTER_INPUT_TITLE = "Register",
        LOGIN_INSTRUCTIONS =
            "Please enter your username and password to login.",
        REGISTER_INSTRUCTIONS =
            "Please enter a username and a password to create an account.",
        LOGIN_MESSAGE =
            "Your account has been created successfully! You can now login.",
        STR_NO_CONNECTED = "Connection to the server failed.\nPlease enter a valid IP "
                           "address and port in the 'Choose IP and Port' menu"
                           "\nor make sure that the server is currently online.",
        STR_CONNECTION_FAILED = "Connection failed.\nPlease enter a valid IP "
                                "address and port or make sure that the server is currently online.",
        STR_CONNECTION_SUCCESS = "Connection made to the server",
        STR_CHOOSE_IP_PORT = "Choose IP and Port",
        STR_IP = "IP address",
        STR_PORT = "Port",
        STR_CONNECT_TO_SERVER = "Connect to server",
        STR_PORT_INVALID = "Port must be a number between 1 and 65535. Port as not been saved in the config file.";

    inline const ftxui::Element WELCOME_TITLE = ftxui::vbox({
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

    inline const ftxui::Element GOODBYE_TITLE = ftxui::vbox({
        ftxui::text(R"(  ______                 _ _                    _ )"),
        ftxui::text(R"( / _____)               | | |                  | |)"),
        ftxui::text(R"(| /  ___  ___   ___   _ | | | _  _   _  ____   | |)"),
        ftxui::text(R"(| | (___)/ _ \ / _ \ / || | || \| | | |/ _  )  |_|)"),
        ftxui::text(R"(| \____/| |_| | |_| ( (_| | |_) ) |_| ( (/ /    _ )"),
        ftxui::text(R"( \_____/ \___/ \___/ \____|____/ \__  |\____)  |_|)"),
        ftxui::text(R"(                                (____/            )"),
    });

    inline const ftxui::Element GAME_OVER_TITLE = ftxui::vbox({
        ftxui::text(
            R"(  _____                         ____                  )"),
        ftxui::text(
            R"( / ____|                       / __ \                 )"),
        ftxui::text(
            R"(| |  __  __ _ _ __ ___   ___  | |  | |__   __ __   __ )"),
        ftxui::text(
            R"(| | |_ |/ _` | '_ ` _ \ / _ \ | |  | |\ \ / / _ \ |__|)"),
        ftxui::text(
            R"(| |__| | (_| | | | | | |  __/ | |__| | \ V /  __/ |   )"),
        ftxui::text(
            R"( \_____|\__,_|_| |_| |_|\___|  \____/   \_/ \___|_|   )"),
    });

    inline const ftxui::Element YOU_WIN_TITLE = ftxui::vbox({
        ftxui::text(R"(__     __          __          ___         _ )"),
        ftxui::text(R"(\ \   / /          \ \        / (_)       | |)"),
        ftxui::text(R"( \ \_/ /__  _   _   \ \  /\  / / _ _ __   | |)"),
        ftxui::text(R"(  \   / _ \| | | |   \ \/  \/ / | | '_ \  | |)"),
        ftxui::text(R"(   | | (_) | |_| |    \  /\  /  | | | | | |_|)"),
        ftxui::text(R"(   |_|\___/ \____|     \/  \/   |_|_| |_| (_))"),
    });

    /**
     * @brief Global style for the buttons
     *
     * @return ftxui::ButtonOption The global style for the buttons
     */
    ftxui::ButtonOption GlobalButtonStyle();

    /**
     * @brief Input option for a password input
     *
     * @return ftxui::InputOption The input option for a password input
     */
    ftxui::InputOption PasswordInputOption();

} // namespace TUI

#endif // TUI_FTXUI_CONFIG_HPP
