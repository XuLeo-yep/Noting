#include <iostream> 
#include <vector>
using namespace std;

int search1 (vector<int>& nums, int target){ //inclusive on both ends
    int left = 0;
    int right = nums.size() - 1;//right-inclusive
    while(left<=right){ //right-inclusive
        int middle = left + (right - left)/2;
        if(nums[middle]>target){
            right = middle -1; //right0inclusive
        } else if (nums[middle]<target){
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;  
}

int search2 (vector<int>& nums, int target){ //left-inclusive and right-exclusive
    int left = 0;
    int right = nums.size();

    while(left < right){
        int middle = left + (right - left) / 2;

        if(nums[middle] > target){
            right = middle;
        } else if (nums[middle] < target){
            left = middle + 1;
        } else {
            return middle;
        }

        return -1;

    }

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
    
    int result = search1(v, 15);
    if (result != -1) {
    cout << "Target found at index: " << result << endl;
    } else {
    cout << "Target not found!" << endl;
    }

    int result1 = search2(v, 15);
    if (result1 != -1) {
    cout << "Target found at index: " << result << endl;
    } else {
    cout << "Target not found!" << endl;
    }


    return 0;   
}