#include <iostream> 
#include <vector>
using namespace std;

class solution{
public:
    vector<vector<int>> generateMatrix(int n){
        vector<vector<int>> res(n,vector<int>(n,0));
        int startX = 0,  startY = 0;
        int i , j;
        int loop = n/2;
        int mid = n/2;
        int count = 1;
        int offset = 1;

        while(loop--){
            i = startX;
            j = startY;

            for(;j < n - offset; j++){
                res[i][j] = count++;
            }

            for(;i < n - offset; i++){
                res[i][j] = count++;
            }

            for(;j > startY ; j--){
                res[i][j] = count++; 
            }

            for(;i > startX ; i--){
                res[i][j] = count++;
            }

            startX++;
            startY++;

            offset++;
        }
        
        if(n%2==1){
            res[mid][mid] = count;
        }
        
        return res;
    }
};

int main(){

    solution sol;

    int n;
    cin >>n;

    vector<vector<int>> v;

    v = sol.generateMatrix(n);

    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if(v[i][j]<10){
                cout<<v[i][j] <<"  ";
            }else{
            cout <<v[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}