#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> completed_orders{0};
std::atomic<bool> stop_requested{false};

void process_order() {
    completed_orders.fetch_add(1, std::memory_order_relaxed);
}

int main() {
    std::vector<std::thread> workers;
    for (int index = 0; index < 4; ++index) {
        workers.emplace_back([] {
            for (int order = 0; order < 100000; ++order) {
                process_order();
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "Completed orders: " << completed_orders.load() << '\n';
    stop_requested.store(true);
    std::cout << "Stop requested: " << std::boolalpha << stop_requested.load() << '\n';
}
