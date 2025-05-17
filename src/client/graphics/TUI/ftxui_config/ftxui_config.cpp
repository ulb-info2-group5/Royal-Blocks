/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ftxui_config.hpp"

namespace TUI {

    ftxui::ButtonOption GlobalButtonStyle() {
        ftxui::ButtonOption buttonStyle;
        buttonStyle.transform = [](const ftxui::EntryState &state) {
            return ftxui::hbox(
                       {ftxui::filler(),
                        ftxui::text(state.label) | ftxui::center | ftxui::bold,
                        ftxui::filler()})
                   | ftxui::xflex
                   | (state.active ? ftxui::color(ftxui::Color::Yellow)
                                   : ftxui::color(ftxui::Color::White))
                   | (state.focused ? ftxui::borderDouble : ftxui::border);
        };
        return buttonStyle;
    }

    ftxui::InputOption PasswordInputOption() {
        ftxui::InputOption passwordOption;
        passwordOption.password = true;
        return passwordOption;
    }

} // namespace TUI
