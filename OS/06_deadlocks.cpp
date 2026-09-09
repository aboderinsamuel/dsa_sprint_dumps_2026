#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

std::mutex first_mutex;
std::mutex second_mutex;

void safe_transfer(int amount) {
    // std::scoped_lock locks both mutexes using a deadlock-avoidance algorithm.
    // It is safer than manually locking first_mutex and then second_mutex.
    std::scoped_lock lock(first_mutex, second_mutex);
    std::cout << "Transferred " << amount << " safely\n";
}

void lock_in_a_consistent_order(int amount) {
    // Another valid strategy: every function takes multiple locks in exactly
    // the same order. If every thread follows the same order, circular waiting
    // cannot form.
    std::lock(first_mutex, second_mutex);
    std::lock_guard<std::mutex> first_lock(first_mutex, std::adopt_lock);
    std::lock_guard<std::mutex> second_lock(second_mutex, std::adopt_lock);
    std::cout << "Transferred " << amount << " with ordered locks\n";
}

int main() {
    std::thread first(safe_transfer, 100);
    std::thread second(lock_in_a_consistent_order, 200);
    first.join();
    second.join();
}

// Broken pattern to recognize in interviews:
// Thread A locks first_mutex, then waits for second_mutex.
// Thread B locks second_mutex, then waits for first_mutex.
// Neither can continue, so both wait forever. That is a deadlock.
