/**
 * @file game_menu.cpp
 * @author Ethan Van Ruyskensvelde
 * @brief Game menu class definition file
 * @date 2025-02-24
 * 
 */

#include "game_menu.hpp"
#include <ftxui/dom/elements.hpp>

// ### Public methods ###

GameMenu::GameMenu(std::shared_ptr<ftxui::ScreenInteractive> screen) : screen_(screen), gameChoice_(PlayMode::NONE) {
    endlessButon_ = ftxui::Button("Endless", [&] { 
        gameChoice_ = PlayMode::ENDLESS;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    duelButon_ = ftxui::Button("Duel", [&] { 
        gameChoice_ = PlayMode::DUEL; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    classicButon_ = ftxui::Button("Classic", [&] { 
        gameChoice_ = PlayMode::CLASSIC; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
    
    royalButon_ = ftxui::Button("Royal", [&] { 
        gameChoice_ = PlayMode::ROYAL; 
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;

    backButton_ = ftxui::Button("Back", [&] {
        gameChoice_ = PlayMode::NONE;
        screen_->ExitLoopClosure()();
    }, ftxui::ButtonOption::Animated(ftxui::Color::Grey0)) | ftxui::border;
}

PlayMode GameMenu::renderAllGames() {
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

    return gameChoice_;
}

PlayMode GameMenu::renderOnlineGames() {
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

    return gameChoice_;
}
