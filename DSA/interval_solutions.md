# Interval Problems Solutions (Prefix Sum / Line Sweep Style)

This guide provides clean C++ solutions using a consistent **Line Sweep / Prefix Sum / Coordinate Compression** style with `using namespace std;` across all standard LeetCode interval problems.

---

## 1. Insert Interval
**Problem Link:** [LeetCode 57](https://leetcode.com/problems/insert-interval/)

### Solution
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // Map stores: time -> {count of starts, count of ends}
        map<int, pair<int, int>> timeline;

        for (const auto& inv : intervals) {
            timeline[inv[0]].first += 1;  // Start event
            timeline[inv[1]].second += 1; // End event
        }
        
        // Add the new interval
        timeline[newInterval[0]].first += 1;
        timeline[newInterval[1]].second += 1;

        vector<vector<int>> result;
        int active_intervals = 0;
        int start_time = -1;

        for (const auto& [time, events] : timeline) {
            int starts = events.first;
            int ends = events.second;

            // If we are currently not inside any interval, and new ones are starting
            if (active_intervals == 0 && starts > 0) {
                start_time = time;
            }

            // Update the running balance of active intervals
            active_intervals += starts - ends;

            // If all intervals that started up to this point have finished closing
            if (active_intervals == 0 && start_time != -1) {
                result.push_back({start_time, time});
                start_time = -1;
            }
        }

        return result;
    }
};

```
// time : 
//space : 
---

## 2. Merge Intervals
**Problem Link:** [LeetCode 56](https://leetcode.com/problems/merge-intervals/)

### Solution
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        map<int, int> timeline;
        
        // Mark boundaries
        for (const auto& inv : intervals) {
            timeline[inv[0]] += 1;
            timeline[inv[1]] -= 1;
        }
        
        vector<vector<int>> result;
        int active_intervals = 0;
        int start_time = -1;
        
        for (const auto& [time, count] : timeline) {
            if (active_intervals == 0 && count > 0) {
                start_time = time;
            }
            active_intervals += count;
            if (active_intervals == 0 && start_time != -1) {
                result.push_back({start_time, time});
                start_time = -1;
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.empty()) return {};
        sort(intervals.begin(), intervals.end());
        result.push_back(intervals[0]);

        for(int i=1; i<intervals.size(); i++){
            if(intervals[i][0] <= result.back()[1]){
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            }else{
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};

---

## 3. Non-Overlapping Intervals
**Problem Link:** [LeetCode 435](https://leetcode.com/problems/non-overlapping-intervals/)

### Solution
*(Note: While line sweep counts overlaps, minimizing removals requires a Greedy sorting strategy by end times to fit the maximum number of intervals).*

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        // Sort by end time to maximize non-overlapping rooms
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int count = 0;
        int last_end = intervals[0][1];
        
        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < last_end) {
                count++; // Overlap detected, remove this interval
            } else {
                last_end = intervals[i][1]; // Update end time
            }
        }
        return count;
    }
};
```

---

## 4. Meeting Rooms
**Problem Link:** [LeetCode 252](https://leetcode.com/problems/meeting-rooms/)

### Solution
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        map<int, int> timeline;
        for (const auto& inv : intervals) {
            timeline[inv[0]] += 1;
            timeline[inv[1]] -= 1;
        }
        
        int current_rooms = 0;
        for (const auto& [time, room_change] : timeline) {
            current_rooms += room_change;
            if (current_rooms > 1) {
                return false; // Multiple meetings overlapping
            }
        }
        return true;
    }
}
```

---

## 5. Meeting Rooms II
**Problem Link:** [LeetCode 253](https://leetcode.com/problems/meeting-rooms-ii/)

### Solution
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> timeline;
        for (const auto& inv : intervals) {
            timeline[inv[0]] += 1;
            timeline[inv[1]] -= 1;
        }
        
        int max_rooms = 0;
        int current_rooms = 0;
        for (const auto& [time, room_change] : timeline) {
            current_rooms += room_change;
            max_rooms = max(max_rooms, current_rooms);
        }
        return max_rooms;
    }
};
```

---

## 6. Meeting Rooms III
**Problem Link:** [LeetCode 2402](https://leetcode.com/problems/meeting-rooms-iii/)

### Solution
*(Note: Requires managing physical room IDs and delay tracking using min-heaps, combined with chronological timeline sorting).*

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Sort meetings by start time
        sort(meetings.begin(), meetings.end());
        
        // Min-heap for available rooms (stores room index)
        priority_queue<int, vector<int>, greater<int>> available_rooms;
        for (int i = 0; i < n; ++i) available_rooms.push(i);
        
        // Min-heap for ongoing meetings: stores {end_time, room_index}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> ongoing;
        
        vector<int> booking_count(n, 0);
        
        for (const auto& m : meetings) {
            long long start = m[0];
            long long end = m[1];
            
            // Release all rooms that finished before or at current start time
            while (!ongoing.empty() && ongoing.top().first <= start) {
                available_rooms.push(ongoing.top().second);
                ongoing.pop();
            }
            
            if (!available_rooms.empty()) {
                int room = available_rooms.top();
                available_rooms.pop();
                ongoing.push({end, room});
                booking_count[room]++;
            } else {
                // No room available, delay the current meeting
                auto [earliest_end, room] = ongoing.top();
                ongoing.pop();
                long long new_end = earliest_end + (end - start);
                ongoing.push({new_end, room});
                booking_count[room]++;
            }
        }
        
        int max_idx = 0;
        for (int i = 1; i < n; ++i) {
            if (booking_count[i] > booking_count[max_idx]) {
                max_idx = i;
            }
        }
        return max_idx;
    }
};
```

---

## 7. Minimum Interval to Include Each Query
**Problem Link:** [LeetCode 1851](https://leetcode.com/problems/minimum-interval-to-include-each-query/)

### Solution
*(Note: Requires sorting queries alongside intervals and utilizing a line-sweep priority queue to efficiently extract the minimum sized interval covering each query location).*

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // Pair up queries with their original indexes to keep track
        vector<pair<int, int>> sorted_queries;
        for (int i = 0; i < queries.size(); ++i) {
            sorted_queries.push_back({queries[i], i});
        }
        
        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());
        // Sort queries by value
        sort(sorted_queries.begin(), sorted_queries.end());
        
        // Min-heap to store: {interval_size, interval_end_time}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> result(queries.size(), -1);
        int i = 0; // index for intervals
        
        for (const auto& [query_val, query_idx] : sorted_queries) {
            // Push all intervals that start before or at the query value
            while (i < intervals.size() && intervals[i][0] <= query_val) {
                int size = intervals[i][1] - intervals[i][0] + 1;
                pq.push({size, intervals[i][1]});
                i++;
            }
            
            // Pop out all intervals that end before the query value
            while (!pq.empty() && pq.top().second < query_val) {
                pq.pop();
            }
            
            // The top of the heap is our smallest valid interval
            if (!pq.empty()) {
                result[query_idx] = pq.top().first;
            }
        }
        
        return result;
    }
};
```
