#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int safe_counter = 0;
std::mutex counter_mutex;

void unsafe_increment_example() {
    // ++counter is a read, add, and write. If multiple threads do it at once,
    // increments can be lost and the program has a data race.
}

void safe_increment() {
    for (int index = 0; index < 100000; ++index) {
        std::lock_guard<std::mutex> lock(counter_mutex);
        ++safe_counter;
    }
}

int main() {
    std::vector<std::thread> workers;
    for (int index = 0; index < 4; ++index) {
        workers.emplace_back(safe_increment);
    }
    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "Safe result: " << safe_counter << " (expected 400000)\n";
}
