#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// BEGINNER IDEA:
// A counter update is not one indivisible action. It is roughly:
//   1. read the old value
//   2. add one
//   3. write the new value
// If two threads interleave those steps, one increment can overwrite another.
// That timing-dependent result is a race condition.
//
// TECHNICAL RULE:
// If threads access the same memory concurrently, at least one access writes,
// and there is no synchronization, the program has a data race. In C++, that
// is undefined behavior. Do not "fix" it by adding sleeps.

int safe_counter = 0;
std::mutex counter_mutex;

void increment_safely() {
    for (int index = 0; index < 100000; ++index) {
        // lock_guard locks here and unlocks automatically at the end of scope.
        // The critical section is deliberately small: only the shared update.
        std::lock_guard<std::mutex> lock(counter_mutex);
        ++safe_counter;
    }
}

int main() {
    // Four threads each add 100,000. The mutex makes the final result reliable.
    std::vector<std::thread> workers;
    for (int index = 0; index < 4; ++index) {
        workers.emplace_back(increment_safely);
    }

    // join means: wait until this worker finishes before leaving main.
    // Without join, main could end while workers are still using the globals.
    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "Safe result: " << safe_counter << " (expected 400000)\n";
}
