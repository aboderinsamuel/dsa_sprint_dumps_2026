#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

class OrderBook {
public:
    void add_quantity(const std::string& symbol, int quantity) {
        std::lock_guard<std::mutex> lock(mutex_);
        quantities_[symbol] += quantity;
    }

    bool execute(const std::string& symbol, int quantity) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto order = quantities_.find(symbol);
        if (order == quantities_.end() || order->second < quantity) {
            return false;
        }

        // The check and subtraction are inside the same critical section.
        // This preserves the invariant: quantity can never become negative.
        order->second -= quantity;
        return true;
    }

    std::map<std::string, int> snapshot() const {
        // Return a copy, not an iterator or reference into protected storage.
        // The caller can safely inspect the copy after this lock is released.
        std::lock_guard<std::mutex> lock(mutex_);
        return quantities_;
    }

private:
    mutable std::mutex mutex_;
    std::map<std::string, int> quantities_;
};

int main() {
    OrderBook book;
    book.add_quantity("AAPL", 1000);

    std::thread trader_one([&book] {
        std::cout << "Trader one: " << book.execute("AAPL", 600) << '\n';
    });
    std::thread trader_two([&book] {
        std::cout << "Trader two: " << book.execute("AAPL", 600) << '\n';
    });
    trader_one.join();
    trader_two.join();

    const auto state = book.snapshot();
    std::cout << "Remaining AAPL quantity: " << state.at("AAPL") << '\n';
}

// Interview discussion:
// - A single mutex is the simplest correct baseline.
// - A larger system might shard locks by symbol to reduce contention.
// - Never expose the map while another thread can mutate it.
// - If execution also updates cash, positions, and trade history, decide whether
//   those fields need one shared lock so the whole trade remains one transaction.
