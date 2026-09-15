//end time >= start time, so we can merge the intervals
//wrap around twick to the original merge intervals problem, we can use the same approach to merge the intervals
#include <vector>
#include <algorithm>
using namespace std;

class ClockIntervalMerger {
public:
    // Each interval is {startMinutes, endMinutes}, both in [0, 1439].
    vector<pair<int,int>> mergeClockIntervals(vector<pair<int,int>>& intervals) {
        vector<pair<int,int>> normalized;

        // Step 1: split any interval that wraps past midnight.
        for (auto& [start, end] : intervals) {
            if (end < start) {
                // Wraps around midnight: e.g. 23:00 -> 02:00.
                // Piece A: from 'start' to the very end of this day.
                normalized.push_back({start, 1439}); // 1439 = 23:59 in minutes
                // Piece B: from the very start of the next day to 'end'.
                normalized.push_back({0, end});
            } else {
                // Already a normal, non-wrapping interval.
                normalized.push_back({start, end});
            }
        }
        // Step 2: sort by start time, as required by the classic merge algorithm.
        sort(normalized.begin(), normalized.end());

        // Step 3: standard interval-merging sweep.
        vector<pair<int,int>> merged;
        for (auto& interval : normalized) {
            if (merged.empty() || merged.back().second < interval.first) {
                // No overlap with the current last merged interval —
                // start a brand new merged interval.
                merged.push_back(interval);
            } else {
                // Overlaps (or touches) the current last merged interval —
                // extend its end if this interval reaches further.
                merged.back().second = max(merged.back().second, interval.second);
            }
        }
        return merged;
    }
};