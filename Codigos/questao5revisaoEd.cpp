#include <iostream>
#include <cstdlib>

using namespace std;



int main(){
    int n=8;
    int vet[n];
    for(int i=0;i<n;i++){
        cin >> vet[i];
    }
    bool vet2[n];
    int vet3[n]={0,0,0,0,0,0,0,0};
    for(int i=0;i<n;i++){
        vet2[i]=false;
    }
    int aux=0;
    while(aux<8){
        vet3[0]=vet[aux];
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(vet3[i]>vet3[j]){
                    swap(vet3[i],vet3[j]);
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(vet3[i]==0){
                    if(vet3[i]==0 and vet[j]==0 and i==j){
                        vet2[j]=false;
                    }else if(vet3[i]==0 and vet[j]==0 and i!=j){
                        vet2[j]=false;
                    }
                }else{
                    vet2[i]=true;
                }
            }
        }
        for(int i=0;i<n;i++){
            if(vet2[i]==true){
                cout << vet3[i] <<" ";
            }
        }
        cout << endl;
        aux++;
    }
    return 0;
}
    
