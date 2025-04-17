#ifndef ABSTRACT_DISPLAY_HPP
#define ABSTRACT_DISPLAY_HPP

#include "../../core/controller/update_type.hpp"

class Controller;

// TODO: doc

class AbstractDisplay {
  public:
    AbstractDisplay() = default;
    AbstractDisplay(const AbstractDisplay &) = default;
    AbstractDisplay(AbstractDisplay &&) = default;
    AbstractDisplay &operator=(const AbstractDisplay &) = default;
    AbstractDisplay &operator=(AbstractDisplay &&) = default;

    virtual void forceRefresh(UpdateType updateType) = 0;

    virtual void run(Controller &controller) = 0;

    virtual ~AbstractDisplay() = default;
};

#endif // ABSTRACT_DISPLAY_HPP
