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

#ifndef UPDATE_TYPE_HPP
#define UPDATE_TYPE_HPP

/**
 * @brief The differents things that can be updated.
 *
 * This is used by the Controller and display-components to talk to each other.
 */
enum class UpdateType {
    FRIENDS_LIST,
    FRIEND_REQUESTS,
    RANKING,
    CONVERSATIONS,
    GAME_STATE,
    OTHER,
};

#endif // UPDATE_TYPE_HPP
