#include <vector>
using namespace std;


class Sea{
public:
    bool hasShips(vector<int> topRight, vector<int> bottomLeft); // Returns true if there is at least one ship in the rectangle represented by the two points, otherwise returns false.
}; 

class Solution{
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft){
        //if the current rectangle doesn't contain any ships, return 0
        if(bottomLeft[0] > topRight[0] || bottomLeft[1] > topRight[1]){
            return 0;
        }
        if(!sea.hasShips(topRight, bottomLeft)){
            return 0;
        }
        // If the rectangle is a single point, return 1
        if(topRight[0] == bottomLeft[0] && topRight[1] == bottomLeft[1]){
            return 1;
        }
        // Otherwise, divide the rectangle into four quadrants and recursively count the ships in each quadrant
        int midX = (topRight[0] + bottomLeft[0]) / 2;
        int midY = (topRight[1] + bottomLeft[1]) / 2;
        return countShips(sea, {midX, midY}, bottomLeft) + // bottom-left quadrant
               countShips(sea, topRight, {midX + 1, midY + 1}) + // top-right quadrant
               countShips(sea, {midX, topRight[1]}, {bottomLeft[0], midY + 1}) + // top-left quadrant
               countShips(sea, {topRight[0], midY}, {midX + 1, bottomLeft[1]}); // bottom-right quadrant
    } 
};

//time : O(nlogn) where n is the number of ships in the rectangle. The recursive function divides the rectangle into four quadrants at each level, 
//and the depth of the recursion is logarithmic with respect to the size of the rectangle.
// space : O(logn) for the recursion stack.

class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        int x1 = bottomLeft[0], y1 = bottomLeft[1]; // bottom-left corner of the rectangle
        int x2 = topRight[0],   y2 = topRight[1]; // top-right corner of the rectangle

        if (x1 > x2 || y1 > y2) return 0; // invalid rectangle

        if (!sea.hasShips(topRight, bottomLeft)) return 0; // no ships in the rectangle

        if (x1 == x2 && y1 == y2) return 1; // the rectangle is a single point and has a ship

        int mx = x1 + (x2 - x1) / 2; // mid-point x-coordinate
        int my = y1 + (y2 - y1) / 2; // mid-point y-coordinate

        return countShips(sea, {mx, my},{x1,y1}) // bottom-left quadrant
             + countShips(sea, {x2, my},{mx + 1, y1}) // bottom-right quadrant 
             + countShips(sea, {mx, y2}, {x1, my + 1}) // top-left quadrant
             + countShips(sea, {x2, y2}, {mx + 1, my + 1}); // top-right quadrant
    } 
};
//for this : time : O(nlogn) where n is the number of ships in the rectangle. The recursive function divides the rectangle into four quadrants at each level,
// and the depth of the recursion is logarithmic with respect to the size of the rectangle.
// space : O(logn) for the recursion stack.