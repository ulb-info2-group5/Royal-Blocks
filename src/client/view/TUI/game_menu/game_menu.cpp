/**
 * @file game_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class definition file
 * @date 2025-02-24
 * 
 */

#include "game_menu.hpp"
#include <ftxui/dom/elements.hpp>

#include "../../../controller/controller.hpp"

// ### Public methods ###

GameMenu::GameMenu(std::shared_ptr<ftxui::ScreenInteractive> &screen, Controller *controller) : screen_(screen), controller_(controller) {
    endlessButon_ = ftxui::Button("Endless", [&] { 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    duelButon_ = ftxui::Button("Duel", [&] { 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    classicButon_ = ftxui::Button("Classic", [&] { 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
    
    royalButon_ = ftxui::Button("Royal", [&] { 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    backButton_ = ftxui::Button("Back", [&] {
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

void GameMenu::renderAllGames() {
    ftxui::Component container = ftxui::Container::Vertical({
        endlessButon_,
        duelButon_,
        classicButon_,
        royalButon_,
        backButton_,
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Select a game mode") | ftxui::center | ftxui::bold,
            ftxui::separator(),
            endlessButon_->Render(),
            duelButon_->Render(),
            classicButon_->Render(),
            royalButon_->Render(),
            ftxui::separator(),
            backButton_->Render(),
        }) | ftxui::border | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_->Loop(renderer);

}

void GameMenu::renderOnlineGames() {
    ftxui::Component container = ftxui::Container::Vertical({
        duelButon_,
        classicButon_,
        royalButon_,
        backButton_,
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Select a game mode") | ftxui::center | ftxui::bold,
            ftxui::separator(),
            duelButon_->Render(),
            classicButon_->Render(),
            royalButon_->Render(),
            ftxui::separator(),
            backButton_->Render(),
        }) | ftxui::border | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_->Loop(renderer);

}
