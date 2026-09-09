#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

class PriceTable {
public:
    void set_price(const std::string& symbol, int price) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        prices_[symbol] = price;
    }

    int get_price(const std::string& symbol) const {
        // Multiple readers may hold a shared lock at the same time.
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto found = prices_.find(symbol);
        return found == prices_.end() ? 0 : found->second;
    }

private:
    mutable std::shared_mutex mutex_;
    std::map<std::string, int> prices_;
};

int main() {
    PriceTable table;
    table.set_price("AAPL", 200);

    std::thread reader_one([&table] { std::cout << table.get_price("AAPL") << '\n'; });
    std::thread reader_two([&table] { std::cout << table.get_price("AAPL") << '\n'; });
    reader_one.join();
    reader_two.join();
}

// A shared_mutex is not automatically faster. If writes are frequent, readers
// can wait often and a normal mutex may be simpler. Measure before optimizing.
