#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_(capacity) {}

    void push(int value) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return values_.size() < capacity_ || closed_; });
        if (closed_) {
            return;
        }
        values_.push(value);
        not_empty_.notify_one();
    }

    bool pop(int& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !values_.empty() || closed_; });
        if (values_.empty()) {
            return false;
        }
        value = values_.front();
        values_.pop();
        not_full_.notify_one();
        return true;
    }

    void close() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }
        not_empty_.notify_all();
        not_full_.notify_all();
    }

private:
    std::size_t capacity_;
    std::queue<int> values_;
    bool closed_ = false;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};

int main() {
    BoundedQueue queue(2);

    std::thread producer([&queue] {
        for (int value = 1; value <= 5; ++value) {
            queue.push(value);
        }
        queue.close();
    });

    std::thread consumer([&queue] {
        int value = 0;
        while (queue.pop(value)) {
            std::cout << "Consumed " << value << '\n';
        }
    });

    producer.join();
    consumer.join();
}
