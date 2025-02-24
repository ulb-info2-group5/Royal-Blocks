/**
 * @file game_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class definition file
 * @date 2025-02-24
 * 
 */

#include "game_menu.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

// ### Public methods ###

GameMenu::GameMenu(std::shared_ptr<ftxui::ScreenInteractive> screen) : screen_(screen) {}

PlayMode GameMenu::render() {
    PlayMode gameChoice = PlayMode::NONE;

    ftxui::Component endlessButon = ftxui::Button("Endless", [&] { 
        gameChoice = PlayMode::ENDLESS;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
    ftxui::Component duelButon = ftxui::Button("Duel", [&] { 
        gameChoice = PlayMode::DUEL; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
    ftxui::Component classicButon = ftxui::Button("Classic", [&] { 
        gameChoice = PlayMode::CLASSIC; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
    ftxui::Component royalButon = ftxui::Button("Royal", [&] { 
        gameChoice = PlayMode::ROYAL; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component backButton = ftxui::Button("Back", [&] {
        gameChoice = PlayMode::NONE;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    ftxui::Component container = ftxui::Container::Vertical({
        endlessButon,
        duelButon,
        classicButon,
        royalButon,
        backButton
    });

    ftxui::Component renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::text("Select a game mode") | ftxui::center | ftxui::bold,
            ftxui::separator(),
            endlessButon->Render(),
            duelButon->Render(),
            classicButon->Render(),
            royalButon->Render(),
            ftxui::separator(),
            backButton->Render(),
        }) | ftxui::border | ftxui::center | ftxui::bgcolor(ftxui::Color::Black);
    });

    screen_->Loop(renderer);

    return gameChoice;
}
