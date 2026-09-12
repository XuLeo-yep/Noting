#include <iostream> 
#include <vector>
using namespace std;

class solution{
public:
    int minSubArrayLen(vector<int>& A,int s){
        int result = INT32_MAX;
        int subLen = 0;
        int i = 0;
        int sum = 0;
        for(int j = 0 ; j < A.size(); j++){
            sum += A[j];

            while (sum >= s){
                subLen = (j - i + 1);
                result = result > subLen ? subLen : result;
                sum -= A[i++];
            }
            
        }
        return result == INT32_MAX ? 0 : result;
    }
};

int main(){
    vector<int> v;

    v.push_back(5);
    v.push_back(3);
    v.push_back(2);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    
    solution sol;

    int res = sol.minSubArrayLen(v,3);

    cout << res << endl;
    return 0;   
}

