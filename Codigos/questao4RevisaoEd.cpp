#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    int vet1[5];
    for(int i=0;i<5;i++){
        cin >> vet1[i];
    }
    int vet2[5];
    for(int i=0;i<5;i++){
        cin >> vet2[i];
    }
    int vet3[10]={0,0,0,0,0,0,0,0,0,0};
    int i=0;
    while(i<10){
        if(i<=4){
            vet3[i]=vet1[i];
        }
        if(i>=5 and i<=9){
            vet3[i]=vet2[i];
        }
        i++;
    }
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(vet3[i]>vet3[j]){
                swap(vet3[i],vet3[j]);
            }
        }
    }
    for(int i=0;i<10;i++){
        cout << vet3[i] <<" ";
    }
    return 0;
}
