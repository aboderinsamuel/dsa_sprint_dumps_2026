#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

// leetcode 295: find median from data stream
class MedianFinder{
private:
    //this is so that we can get the maximum element from the left side of the median
    //why? : because we want to get the maximum element from the left side of the median, we will use a max heap for that
    //why do we get the max heap for only the leftside first? : this is so that we can get the maximum element from the left side of the median, and then we can get the minimum element from the right side of the median, and then we can get the median by taking the average of the two elements

    priority_queue<int> maxHeap; //left side of the median
    priority_queue<int, vector<int>, greater<int>> minHeap; //right side of the median
public:
    MedianFinder() {
    }
    void addNum(int num){
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if(maxHeap.size() < minHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian(){
        if(maxHeap.size() > minHeap.size()) return maxHeap.top();
        else return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
// leetcode 480: sliding window median
vector<double> medianSlidingWindow(vector<int>& nums, int k)
{
    vector<double> medians;
    multiset<int> window(nums.begin(), nums.begin() + k);

    auto mid = next(window.begin(), k / 2);

    for (int i = k;; i++) {

        // Push the current median
        medians.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

        // If all done, break
        if (i == nums.size())
            break;

        // Insert incoming element
        window.insert(nums[i]);
        if (nums[i] < *mid)
            mid--;                  // same as mid = prev(mid)

        // Remove outgoing element
        if (nums[i - k] <= *mid)
            mid++;                  // same as mid = next(mid)

        window.erase(window.lower_bound(nums[i - k]));
    }

    return medians;
}
//leetcode 502: IPO
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    vector<pair<int,int>> projects(n);
    for(int i=0; i<n; i++){
        projects[i] = {capital[i], profits[i]};
    }
    sort(projects.begin(), projects.end());
    priority_queue<int> maxHeap;
    int i=0;
    while(k--){
        while(i<n && projects[i].first <= w){
            maxHeap.push(projects[i].second);
            i++;
        }
        if(maxHeap.empty()) break;
        w += maxHeap.top();
        maxHeap.pop();
    }
    return w;
}
