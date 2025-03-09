#ifndef IMESSAGE_HPP
#define IMESSAGE_HPP

#include <string>

enum class MessagingState {
    BACK,
    NONE,
};

struct Message {
    int idSender;
    std::string message;
};

class IMessage {
  protected:
    virtual void createButtons() = 0;

    virtual void drawInputUSer() = 0;

    virtual void drawMenu() = 0;

    virtual void drawDisplay() = 0;

    virtual void drawWindow() = 0;

  public:
    virtual ~IMessage() = default;

    virtual void render() = 0;
};

#endif // IMESSAGE_HPP
