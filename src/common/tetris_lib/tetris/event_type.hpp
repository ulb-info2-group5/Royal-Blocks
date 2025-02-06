#ifndef EVENT_TYPE_HPP
#define EVENT_TYPE_HPP

/**
 * @enum EventType
 *
 * @brief Represents different types of events that can notify the Tetris
 * class.
 */
enum class EventType {
    None,
    BigDrop,
    MoveDown,
    MoveLeft,
    MoveRight,
    ClockTick,
    RotateClockwise,
    RotateCounterClockwise,
    Quit,
};

#endif
