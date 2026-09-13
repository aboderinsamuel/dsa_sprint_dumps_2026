class collatzCounter{
public:
    int countSteps(long long n){
        if(n <= 0) return -1;

        int steps =  0;
        while(n != 1){
            if(n % 2 == 0){
                n = n/2;
            }
            else{
                n = 3*n + 1;
            }
            steps++;
        }
        return steps;
    }
};
//Time O(k) where k is the number of steps to reach 1
//Space O(1) since we are using a constant amount of space

