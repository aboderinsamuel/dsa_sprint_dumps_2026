#include <deque>
#include <utility>
#include <optional>
#include <cmath>

using namespace std;

class PriceWindow{
    int windowSeconds;
    deque<pair<long long, double>> maxDeque; // pair of timestamp and price
    deque<pair<long long, double>> minDeque; // pair of timestamp and price
    bool triggered = false; // flag to indicate if the threshold has been triggered

public:
    explicit PriceWindow(int windowSeconds = 600) : windowSeconds(windowSeconds) {}

    void addPrice(long long timestamp, double price) {
        // Remove old prices from the deques
        while (!maxDeque.empty() && maxDeque.front().first <= timestamp - windowSeconds) {
            maxDeque.pop_front();
        }
        while (!minDeque.empty() && minDeque.front().first <= timestamp - windowSeconds) {
            minDeque.pop_front();
        }

        // Add new price to the deques
        while (!maxDeque.empty() && maxDeque.back().second < price) {
            maxDeque.pop_back();
        }
        maxDeque.emplace_back(timestamp, price);

        while (!minDeque.empty() && minDeque.back().second > price) {
            minDeque.pop_back();
        }
        minDeque.emplace_back(timestamp, price);
    }
    optional<double> getMaxPrice() const {
        if (maxDeque.empty()) return nullopt;
        return maxDeque.front().second;
    }
    optional<double> getMinPrice() const {
        if (minDeque.empty()) return nullopt;
        return minDeque.front().second;
    }
    bool checkChange(double threshold = 0.10) {
        if (maxDeque.empty() || minDeque.empty()) return false;

        double maxPrice = maxDeque.front().second;
        double minPrice = minDeque.front().second;

        // Calculate percentage change
        double percentageChange = (maxPrice - minPrice) / minPrice;

        // Check if the change exceeds the threshold
        if (percentageChange >= threshold && !triggered) {
            triggered = true;
            return true;
        }
        else if(percentageChange < threshold && triggered) {
            triggered = false; // Reset the trigger if the change goes below the threshold
        }
        return false;
    }
};