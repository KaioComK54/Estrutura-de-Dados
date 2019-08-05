#include <iostream>

using namespace std;

int main(){
    int mat[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cin >> mat[i][j];
        }
    }
    int maior=0;
    int posMaior=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(mat[i][j]>maior){
                maior=mat[i][j];
                posMaior=i;
            }
        }
    }
    int menor=maior;
    int posMenor=0;
    for(int i=posMaior;i>posMaior-1;i--){
        for(int j=9;j>=0;j--){
            if(menor>mat[i][j]){
                menor=mat[i][j];
                posMenor=j;
            }
        }
    }
    cout << menor << endl;
    cout << posMaior <<" "<< posMenor << endl;
    return 0;
}
