#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

struct Transaction{
    string name;
    int time;
    int amount;
    string city;
};

class InvalidTransactionFinder{
public:
    vector<Transaction> findInvalidTransactions(vector<Transaction>& transactions){
        int n = transactions.size();
        //map each person's name to the list of INDICES of their transactions
        // we store indices(not copies of the transaction objects) so we can
        //easily mark them invalid by index later without duplicating the transaction objects
        unordered_map<string, vector<int>> byPerson;
        for(int i=0; i<n; i++){
            byPerson[transactions[i].name].push_back(i);
        }
        //we use a set of indices to avoid adding the same transaction
        //twice to the final result if it fails multiple checks
        unordered_set<int> invalidIndices;
        for(int i=0; i<n; i++){
            //RULE1: Amount too large
            if(transactions[i].amount > 1000){
                invalidIndices.insert(i);
            }
            //RULE2: Same name, different city, within 60 minutes
            for(int j : byPerson[transactions[i].name]){
                if(i == j) continue; //skip self

                bool differentCity = transactions[i].city != transactions[j].city;
                bool within60Minutes = abs(transactions[i].time - transactions[j].time) <= 60;

                if(differentCity && within60Minutes){
                    invalidIndices.insert(i);
                    break; //one match is enough to mark this transaction invalid, no need to check further
                }
            }
        }
        //build the final result from the marked invalid indices
        vector<Transaction> result;
        for(int index : invalidIndices){
            result.push_back(transactions[index]);
        }
        return result;
    }
};
///////////////////////////////////////////////////////////////////OR///////////////////////////////////////////////////////////////
vector<string> invalidTransactions(vector<string>& transactions){
    int n = transactions.size();
    vector<string> name(n);
    vector<int> time(n);
    vector<int> amount(n);
    vector<string> city(n);
    //parse every transaction
    for(int i=0; i<n; i++){
        stringstream ss(transactions[i]);
        string timeStr, amountStr;
        getline(ss, name[i], ',');
        getline(ss, timeStr, ',');
        getline(ss, amountStr, ',');
        getline(ss, city[i], ',');
        time[i] = stoi(timeStr);
        amount[i] = stoi(amountStr);
    }
    vector<bool> invalid(n, false);
    for(int i=0; i<n; i++){
        //RULE1: Amount too large
        if(amount[i] > 1000){
            invalid[i] = true;
        }
        //RULE2: Same name, different city, within 60 minutes
        for(int j=0; j<n; j++){
            if(i == j) continue; //skip self

            bool sameName = name[i] == name[j];
            bool differentCity = city[i] != city[j];
            bool within60Minutes = abs(time[i] - time[j]) <= 60;

            if(sameName && differentCity && within60Minutes){
                invalid[i] = true;
                break; //one match is enough to mark this transaction invalid, no need to check further
            }
        }
    }
    //build the final result from the marked invalid indices
    vector<string> result;
    for(int i=0; i<n; i++){
        if(invalid[i]){
            result.push_back(transactions[i]);
        }
    }
    return result;
}
//time: O(n^2)
//space: O(n)
