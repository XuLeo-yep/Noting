#include <iostream> 
#include <vector>
using namespace std;

class solution{
public:
    vector<int> sortedSquare(vector<int>& A){
         int k = A.size()-1;
         vector<int> result(A.size(),0);
         for(int i = 0, j = A.size() - 1 ; i <= j;){
            if(A[i] * A[i] > A[j] * A[j]){
                result[k--] = A[i] * A[i];
                
                i++;
            } else {
                result[k--] = A[j] * A[j];

                j--;
            }
         }
         return result;
    }
};

int main(){
    vector<int> v;

    v.push_back(-5);
    v.push_back(-3);
    v.push_back(-2);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    
    solution sol;

    for(int i = 0; i < v.size(); i++){
        cout <<v[i]<<" ";
        cout << endl;   
    }
    
    cout<<"------------"<<endl;

    v=sol.sortedSquare(v);

    for(int i = 0; i < v.size(); i++){
        cout <<v[i]<<" ";
        cout << endl;   
    }



    return 0;   
}