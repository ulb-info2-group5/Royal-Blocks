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

#ifndef ABSTRACT_DISPLAY_HPP
#define ABSTRACT_DISPLAY_HPP

class Controller;

enum class UpdateType;

/**
 * @brief Absstract class for displays such as TUI and GUI.
 */
class AbstractDisplay {
  protected:
    Controller &controller_;

  public:
    AbstractDisplay() = delete;
    AbstractDisplay(const AbstractDisplay &) = default;
    AbstractDisplay(AbstractDisplay &&) = default;
    explicit AbstractDisplay(Controller& controller);
    AbstractDisplay &operator=(const AbstractDisplay &) = delete;
    AbstractDisplay &operator=(AbstractDisplay &&) = delete;

    /**
     * @brief Forces the screen to refresh the things related to the given
     * updateType.
     */
    virtual void forceRefresh(UpdateType updateType) = 0;

    /**
     * @brief Runs the display.
     */
    virtual void run() = 0;

    virtual ~AbstractDisplay() = default;

    /**
     * @brief Called when the client is disconnected from the server.
     */
    virtual void onDisconnected() = 0;
};

#endif // ABSTRACT_DISPLAY_HPP
