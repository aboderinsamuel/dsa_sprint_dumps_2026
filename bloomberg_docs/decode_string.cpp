#include <string>
#include <stack>
using namespace std;

class Decoder{
public:
    string decodeString(string s){
        stack<int> numberStack;
        stack<string> stringStack;
        

        // this is to keep track of the string before the current string
        //example : "3[a]2[bc]" -> "aaabcbc"
        //the string before the current string is 
        // "aaabcbc" and the current string is "bc"

        int currentNumber = 0;
        string currentString = "";
        

        for(char c : s){
            if(isdigit(c)){
                currentNumber = currentNumber*10 + (c - '0');
                //what this does is this:
                // if the current number is 3 and the next digit is 4, then the current number 
                // becomes 34
                // this is because we are building the number digit by digit
            }
            else if(c == '['){
                //we're about to go one level deeper, save the current
                // multiplier and the string built so far at this level,
                //then reset for the fresh nested content
                numberStack.push(currentNumber);
                stringStack.push(currentString);
                currentNumber = 0;
                currentString = "";
            }
            else if(c == ']'){
                //we've just finished reading one full nested block
                //pop what multiplier applies to it and what string
                //it needs to be glued onto.
                int repeatCount = numberStack.top();
                string outerString = stringStack.top();


                numberStack.pop();
                stringStack.pop();

                //repeeat the nested content 'repeatCount' times and glue it onto the outer string
                string repeated = "";
                for(int i=0; i<repeatCount; i++){
                    repeated += currentString;
                }
                currentString = outerString + repeated;
            }
            else{
                currentString += c;
            }
        }
        return currentString;
    }
};