#ifndef IMESSAGE_HPP
#define IMESSAGE_HPP

#include <string>

class IMessage {
  protected:
    virtual void drawButtons() = 0;

    virtual void drawInputUSer() = 0;

    virtual void drawMenu() = 0;

    virtual void drawDisplay() = 0;

    virtual void drawWindow() = 0;

  public:
    virtual ~IMessage() = default;

    // virtual void addFriend(std::string friendName) = 0;

    virtual void addMessage(const std::string &message) = 0;
};

#endif // IMESSAGE_HPP
