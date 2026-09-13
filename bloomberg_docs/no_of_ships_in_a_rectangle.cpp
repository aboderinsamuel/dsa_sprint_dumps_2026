// (DIVIDE AND CONQUER SEARCH)
//LEETCODE 1274 (PREMIUM) : Number of ships in a rectangle
//QUADTREE SEARCH

#include <vector>
using namespace std;

// Reps the points on the grid
struct Point {
    int x, y;
};
// This would be provided by the interviewer/problem — a black-box API.
// It tells you whether at least one ship lies within the rectangle
// defined by bottomLeft and topRight (inclusive).
class Sea{
public:
    bool hasShips(Point topRight, Point bottomLeft);
};

class ShipCounter{
public:
    int countShips(Sea sea, Point topRight, Point bottomLeft){
        //Base case 1: invalid/empty rectangle
        if(bottomLeft.x > topRight.x || bottomLeft.y > topRight.y) return 0;
        //Base case 2: ask the API: is there any ship in this whole region?
        //if not discard all
        if(!sea.hasShips(topRight, bottomLeft)) return 0;
        //Base case 3: if the rectangle is a single point, and there is a
        //ship there, return 1
        if(bottomLeft.x == topRight.x && bottomLeft.y == topRight.y) return 1;
        //Divide and conquer: split the rectangle into four quadrants
        //around the mid point
        int midX = (bottomLeft.x + topRight.x) / 2;
        int midY = (bottomLeft.y + topRight.y) / 2;
        //Count the ships in each quadrant recursively
        int count = 0;
        //bottom-left quadrant
        count += countShips(sea, {midX, midY}, bottomLeft);
        //bottom-right quadrant
        count += countShips(sea, {topRight.x, midY}, {midX+1, bottomLeft.y});
        //top-left quadrant
        count += countShips(sea, {midX, topRight.y}, {bottomLeft.x, midY+1});
        //top-right quadrant
        count += countShips(sea, topRight, {midX+1, midY+1});
        return count;
    }
};
