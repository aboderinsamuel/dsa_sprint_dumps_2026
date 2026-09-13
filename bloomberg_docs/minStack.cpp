#include <stack>
#include <climits>
using namespace std;

class MinStack{
private:
    stack<int> mainStack; //holds actual values
    stack<int> minStack; //minStack.top() is always the current minimum
public:
    MinStack(){}
    void push(int val){
        mainStack.push(val);
        if(minStack.empty()){
            minStack.push(val);
        }
        else{
            minStack.push(min(val, minStack.top()));
        }
    }
    void pop(){
        mainStack.pop();
        minStack.pop(); 
    }
    int top(){
        return mainStack.top();
    }
    int getMin(){
        return minStack.top();
    }
};
// time: O(1)
//space:O(n)



