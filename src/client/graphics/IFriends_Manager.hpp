#ifndef IFRIENDS_MANAGER_HPP
#define IFRIENDS_MANAGER_HPP

#include <string>

class IFriends_Manager {
  private:
    // virtual void displayFriendButtons(const std::vector<std::string>
    // &friendsList) = 0;

    virtual void manageFriendlistScreen(const std::string &friendName) = 0;

    /*
     * @brief Screen to add a friend
     */
    virtual void addFriendScreen() = 0;

  public:
    /*
     * @brief Destroy the Friends Manager object
     */
    virtual ~IFriends_Manager() = default;

    /*
     * @brief Render the friends manager screen with all the components
     */
    virtual void render() = 0;
};

#endif