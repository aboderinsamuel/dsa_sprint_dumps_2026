#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int calculate_total(int quantity, int price) {
    if (quantity < 0) {
        throw std::invalid_argument("quantity cannot be negative");
    }
    return quantity * price;
}

int main() {
    // async starts work and returns a future representing a result that may not
    // be ready yet. Calling get waits, then returns the result or rethrows the
    // exception that happened inside the worker.
    std::future<int> result = std::async(std::launch::async, calculate_total, 5, 100);
    std::cout << "Total: " << result.get() << '\n';

    auto failed_result = std::async(std::launch::async, calculate_total, -1, 100);
    try {
        failed_result.get();
    } catch (const std::exception& error) {
        std::cout << "Worker error: " << error.what() << '\n';
    }
}
