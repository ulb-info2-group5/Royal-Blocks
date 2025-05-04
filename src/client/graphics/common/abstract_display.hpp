#ifndef ABSTRACT_DISPLAY_HPP
#define ABSTRACT_DISPLAY_HPP

#include "../../core/controller/update_type.hpp"

class Controller;

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
