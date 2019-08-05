#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    int mat[10][10];
    int mat1[10][10];
    int mat2[10][10];
    int mat3[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cin >> mat[i][j];
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            mat1[i][j]=mat[i][j];
            mat2[i][j]=mat[i][j];
            mat3[i][j]=mat[i][j];
        }
    }
    cout <<'1'<<'.'<< endl;
    int aux = 0;
    while(aux<10){
        swap(mat[1][aux],mat[7][aux]);
        ++aux;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    cout <<'2'<<'.'<< endl;
    int aux2=0;
    while(aux2<10){
        swap(mat1[aux2][3],mat1[aux2][9]);
        ++aux2;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat1[i][j] <<" ";
        }
        cout << endl;
    }
    cout <<'3'<<'.'<< endl;
    int a=0;
    int b=9;
    cout << endl;
    int i=0;
    while(a<10 and b>=0 and i<10){
        swap(mat2[i][i],mat2[a][b]);
        ++a;
        ++i;
        --b;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat2[i][j] <<" ";
        }
        cout << endl;
    }
    cout <<'3'<<'.'<< endl;
    int cont1=0;
    int cont2=0;
    while(cont1<10 and cont2<10){
        swap(mat3[4][cont1],mat3[cont2][9]);
        ++cont1;
        ++cont2;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout << mat3[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}
        
