#include <iostream> 
#include <vector>
using namespace std;

class solution{
public:
    int removeElement(vector<int>& nums,int val){
        int slowIndex = 0;
        
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex ++){
            if(nums[fastIndex] != val){
                nums[slowIndex++] = nums[fastIndex];
            
            }
        }
        return slowIndex;
    }
};

int main(){
    vector<int> v;

    v.push_back(10);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    v.push_back(15);
    v.push_back(16);
    v.push_back(17);
    v.push_back(19);
    
    solution sol;

    int val = 12;

    int newLength = sol.removeElement(v,val);

    cout <<"new length "<<newLength<< endl;

    for(int i = 0; i < newLength; i++){
        cout <<v[i]<<" ";
        cout << endl;   
    }



    return 0;   
}