#include <iostream> //inclusive on both ends
#include <vector>
using namespace std;

int search (vector<int>& nums, int target){
    int left = 0;
    int right = nums.size() - 1;
    while(left<=right){
        int middle = left + (right - left)/2;
        if(nums[middle]>target){
            right = middle -1;
        } else if (nums[middle]<target){
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;  
}
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
    
    int result = search(v, 15);
    if (result != -1) {
    cout << "Target found at index: " << result << endl;
    } else {
    cout << "Target not found!" << endl;
    }


    return 0;   
}