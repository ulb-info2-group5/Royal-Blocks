#ifndef EVENT_TYPE_HPP
#define EVENT_TYPE_HPP

/**
 * @enum EventType
 *
 * @brief Represents different types of events that can notify the Tetris
 * class.
 *
 * The EventType enum defines the possible actions or occurrences
 * in the game, allowing the Tetris class to respond appropriately.
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
};

#endif
