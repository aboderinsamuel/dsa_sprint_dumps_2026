
// leetcode.com/problems/merge-k-sorted-lists/
//leetcode 23: Merge k Sorted Lists
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution{
private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode dummy;
        ListNode* tail = &dummy;
        while(l1 && l2){
            if(l1->val <= l2->val){
                tail->next = l1;
                l1 = l1->next;
            }else{
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists){
        if(lists.empty()) return nullptr;
        int k = lists.size();
        while(k > 1){
            for(int i=0; i<k/2; i++){
                lists[i] = mergeTwoLists(lists[i], lists[k-1-i]);
            }
            k = (k+1)/2;
        }
        return lists[0];
    }
};

// leetcode 378: Kth Smallest Element in a Sorted Matrix
// Medium
// Topics
// premium lock icon
// Companies
// Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.

// Note that it is the kth smallest element in the sorted order, not the kth distinct element.

// You must find a solution with a memory complexity better than O(n2).

 

// Example 1:

// Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
// Output: 13
// Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
// Example 2:

// Input: matrix = [[-5]], k = 1
// Output: -5
 
class Solution2 {
private:
    class MyHeapNode{
    public:
        int row;
        int column;
        int value;

        MyHeapNode(int v, int r, int c) : value(v), row(r), column(c) {}
    };
    class MyHeapComparator{
    public:
        bool operator()(const MyHeapNode& x, const MyHeapNode& y) const {
            return x.value > y.value;
        }
    };
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<MyHeapNode, vector<MyHeapNode>, MyHeapComparator> minHeap;
        for(int row = 0; row < min(n, k); row++){
            minHeap.push(MyHeapNode(matrix[row][0], row, 0));
        }
        MyHeapNode element(0, 0, 0);
        while(k-- > 0){
            element = minHeap.top();
            minHeap.pop();
            int row = element.row;
            int column = element.column;

            if(column < n-1){
                minHeap.push(MyHeapNode(matrix[row][column+1], row, column+1));
            }
        }
        return element.value;
    }
};


class Solution3{
private:
    //helper function to count elements <= target in O(N) tme
    int countLessEqual(vector<vector<int>>& matrix, int target, int n){
        int count = 0;
        int row = n-1;
        int col = 0;

        while(row >= 0 && col < n){
            if(matrix[row][col] <= target){
                count += row +1;
                col++;
            }
            else{
                row--;
            }
        }
        return count;
    }
public:
    int kthSmallest(vector<vector<int>>& matrix, int k){
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n-1][n-1];
        int ans = low;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(countLessEqual(matrix, mid, n) < k){
                low = mid + 1;
            }
            else{
                ans = mid;
                high = mid - 1;
            }
        }
        return ans;
    }
};