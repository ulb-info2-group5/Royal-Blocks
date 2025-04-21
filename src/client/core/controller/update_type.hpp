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
