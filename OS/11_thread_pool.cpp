#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t worker_count) {
        for (std::size_t index = 0; index < worker_count; ++index) {
            workers_.emplace_back([this] { worker_loop(); });
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stopping_ = true;
        }
        condition_.notify_all();
        for (auto& worker : workers_) {
            worker.join();
        }
    }

    void submit(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (stopping_) {
                return;
            }
            tasks_.push(std::move(task));
        }
        condition_.notify_one();
    }

private:
    void worker_loop() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                condition_.wait(lock, [this] {
                    return stopping_ || !tasks_.empty();
                });
                if (stopping_ && tasks_.empty()) {
                    return;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }
            // Execute outside the lock: other workers must be able to receive work.
            task();
        }
    }

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stopping_ = false;
};

int main() {
    ThreadPool pool(2);
    for (int task_id = 1; task_id <= 5; ++task_id) {
        pool.submit([task_id] {
            std::cout << "Running task " << task_id << '\n';
        });
    }
    // The destructor closes the queue, wakes workers, and joins them.
}
