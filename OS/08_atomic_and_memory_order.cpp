#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> data_ready{false};
int data = 0;

void producer() {
    data = 42;
    // Release says earlier writes become visible to an acquiring reader that
    // observes this store. The atomic flag is both the signal and the ordering.
    data_ready.store(true, std::memory_order_release);
}

void consumer() {
    while (!data_ready.load(std::memory_order_acquire)) {
        // Acquire pairs with the producer's release store.
        // In real high-throughput code, consider wait/notify or a condition variable
        // instead of spinning continuously.
    }
    std::cout << "Data: " << data << '\n';
}

int main() {
    std::thread reader(consumer);
    std::thread writer(producer);
    writer.join();
    reader.join();

    std::atomic<int> count{0};
    count.fetch_add(1, std::memory_order_relaxed);
    std::cout << "Atomic count: " << count.load() << '\n';
}

// Beginner rule: use the default sequentially-consistent ordering until you
// can explain acquire, release, relaxed, and happens-before. A mutex is often
// clearer when several fields must change together.
