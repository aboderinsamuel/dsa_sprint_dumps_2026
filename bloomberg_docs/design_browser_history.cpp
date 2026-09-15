#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BrowserHistory{
private:
    vector<string> history; // store the history of visited URLs
    int current; // index of the current page in the history
public:
    BrowserHistory(string homepage){
        history.push_back(homepage);
        current = 0;
    }
    void visit(string url){
        // When visiting a new URL, we need to discard all forward history
        history.resize(current + 1); // remove forward history
        history.push_back(url);
        current++;
    }
    string back(int steps){
        current = max(0, current - steps); // move back but not beyond the first page
        return history[current];
    }
    string forward(int steps){
        current = min((int)history.size() - 1, current + steps); // move forward but not beyond the last page
        return history[current];
    }
};
