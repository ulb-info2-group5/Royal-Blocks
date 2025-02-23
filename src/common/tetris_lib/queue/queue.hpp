#ifndef SERIALIZABLE_QUEUE_HPP
#define SERIALIZABLE_QUEUE_HPP

#include <nlohmann/json.hpp>

#include <deque>
#include <optional>

/**
 * @brief A double-ended queue that can be serialized.
 *
 * @tparam T The type of objects stored in the queue.
 */
template <typename T> class Queue {
  protected:
    std::deque<T> queue_;

  public:
    Queue() = default;
    Queue(const Queue &) = default;
    Queue(Queue &&) = default;
    Queue &operator=(const Queue &) = default;
    Queue &operator=(Queue &&) = default;

    ~Queue() = default;

    /**
     * @brief Returns the queue's size.
     */
    size_t size() const noexcept { return queue_.size(); };

    /**
     * @brief Pushes a new T to the back of the queue.
     */
    void pushBack(const T &elem) { queue_.push_back(elem); }

    /**
     * @brief Pushes a new T to the front of the queue.
     */
    void pushFront(const T &elem) { queue_.push_front(elem); }

    /**
     * @brief Returns a mutable reference to the element at the front of the
     * queue.
     */
    T &front() { return queue_.front(); }

    /**
     * @brief Returns a mutable reference to the element at the back of the
     * queue.
     */
    T &back() { return queue_.back(); }

    /**
     * @brief Removes the next T at the front of the queue and returns it
     * (wrapped in an std::optional, nullopt if the queue was already empty).
     */
    std::optional<T> popFront() {
        if (queue_.empty()) {
            return std::nullopt;
        } else {
            std::optional<T> next = std::move(front());
            queue_.pop_front();
            return next;
        }
    }
};

#endif // SERIALIZABLE_QUEUE_HPP
