#include <iostream>
#include <map>
#include <mutex>
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
        order->second -= quantity;
        return true;
    }

    std::map<std::string, int> snapshot() const {
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

    std::thread buyer_one([&book] { book.execute("AAPL", 600); });
    std::thread buyer_two([&book] { book.execute("AAPL", 600); });
    buyer_one.join();
    buyer_two.join();

    const auto state = book.snapshot();
    std::cout << "Remaining AAPL quantity: " << state.at("AAPL") << '\n';
}
