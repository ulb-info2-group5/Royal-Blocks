#ifndef ABSTRACT_DISPLAY_HPP
#define ABSTRACT_DISPLAY_HPP

#include "../../core/controller/update_type.hpp"

class Controller;

/**
 * @brief Absstract class for displays such as TUI and GUI.
 */
class AbstractDisplay {
  public:
    AbstractDisplay() = default;
    AbstractDisplay(const AbstractDisplay &) = default;
    AbstractDisplay(AbstractDisplay &&) = default;
    AbstractDisplay &operator=(const AbstractDisplay &) = default;
    AbstractDisplay &operator=(AbstractDisplay &&) = default;

    /**
     * @brief Forces the screen to refresh the things related to the given
     * updateType.
     */
    virtual void forceRefresh(UpdateType updateType) = 0;

    /**
     * @brief Runs the display.
     */
    virtual void run(Controller &controller) = 0;

    virtual ~AbstractDisplay() = default;
};

#endif // ABSTRACT_DISPLAY_HPP
