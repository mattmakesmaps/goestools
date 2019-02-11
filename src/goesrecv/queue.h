#pragma once

#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>

#include <util/error.h>

template <class T>
class Queue {
public:
  Queue(size_t capacity) :
      elements_(0),
      capacity_(capacity),
      closed_(false) {
  }

  size_t size() {
    /*
     * unique_lock allows for only a single thread
     * to have access to the resource at a given time.
     * The thread working will have ownership of the mutex.
     * I believe that the lock is released at the end
     * of the block scope.
     *
     * I don't know why `unique_lock` was used over
     * `lock_guard`. The answer is in the conditional variables usage:
     * - `cv_.notify_one()`
     * - `cv_.wait()`
     */
    std::unique_lock<std::mutex> lock(m_);
    return elements_;
  }

  bool closed() {
    std::unique_lock<std::mutex> lock(m_);
    return closed_;
  }

  void close() {
    std::unique_lock<std::mutex> lock(m_);
    closed_ = true;
    cv_.notify_one();
  }

  // popForWrite returns existing item to write to
  std::unique_ptr<T> popForWrite() {
    std::unique_lock<std::mutex> lock(m_);
    ASSERT(!closed_);

    // Ensure there is an item to return
    // MK NOTE:
    // - If empty, and if we have capacity add a new pointer
    //   to the template type.
    // - If empty, and if we don't have capacity, block.
    if (write_.size() == 0) {
      if (elements_ < capacity_) {
        elements_++;
        write_.push_back(std::make_unique<T>());
      } else {
        // Wait until pushRead makes an item available
        while (write_.size() == 0) {
          cv_.wait(lock);
        }
      }
    }

    // MK NOTE: We know we have an element to return.
    // Move operation on unique pointer of template type
    // in front of queue `write_` aliased to `v`.
    auto v = std::move(write_.front());
    // MK NOTE: I believe that the front of `write_`
    // is now a nullptr. so we remove it.
    write_.pop_front();
    return v;
  }

  // pushWrite returns written item to read queue
  void pushWrite(std::unique_ptr<T> v) {
    std::unique_lock<std::mutex> lock(m_);
    ASSERT(!closed_);

    read_.push_back(std::move(v));
    cv_.notify_one();
  }

  // popForRead returns existing item to read from
  std::unique_ptr<T> popForRead() {
    std::unique_lock<std::mutex> lock(m_);
    // MK NOTE: block until `read_` queue has an item.
    // will be notified by `pushWrite()`
    while (read_.size() == 0 && !closed_) {
      cv_.wait(lock);
    }

    // Allow read side to drain
    // MK NOTE: drain in this context means
    // just return nullptr. This can only
    // happen if the Queue is closed AND
    // read_ is empty.
    if (read_.size() == 0 && closed_) {
      return std::unique_ptr<T>(nullptr);
    }

    // MK NOTE: See above for annotation from
    // `popForWrite()`.
    auto v = std::move(read_.front());
    read_.pop_front();
    return v;
  }

  // pushRead returns read item to write queue
  void pushRead(std::unique_ptr<T> v) {
    // MK NOTE: Same as `pushWrite()`.
    // add a "read" item to the `write_` queue
    // and unblock it.
    std::unique_lock<std::mutex> lock(m_);
    if (!closed_) {
      write_.push_back(std::move(v));
      cv_.notify_one();
    }
  }

protected:
  std::mutex m_;
  std::condition_variable cv_;

  size_t elements_;
  size_t capacity_;
  bool closed_;

  std::deque<std::unique_ptr<T> > write_;
  std::deque<std::unique_ptr<T> > read_;
};
