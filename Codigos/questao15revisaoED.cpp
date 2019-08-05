#include <iostream>
#include <fstream>

using namespace std;

int Fibo(int n){
    if(n==0){
        return 0;
    }else if(n==1){
        return 1;
    }
    return Fibo(n-1)+Fibo(n-2);
}

int main(){
    string nome;
    cin >> nome;
    int n;
    cin >> n;
    int vet[n];
    for(int i=0;i<n;i++){
        vet[i]=Fibo(i);
    }
    ofstream arquivo(nome.c_str());
    for(int i=0;i<n;i++){
        if(vet[i]%2==0){
            arquivo << vet[i] <<" ";
        }
    }
    return 0;
}
    
