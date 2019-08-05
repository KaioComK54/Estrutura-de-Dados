#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    int mat[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cin >> mat[i][j];
        }
    }
    cout << 1 <<'.'<< endl;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(i==1){
                swap(mat[i][j],mat[7][j]);
            }
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    cout << 2 <<'.'<< endl;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(j==3){
                swap(mat[i][j],mat[i][9]);
            }
        }
    }
    cout << endl;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}
            

