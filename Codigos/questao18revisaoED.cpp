#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    ifstream arquivo("entrada.txt");
    ofstream arquivo2("saida.txt");
    if(arquivo and arquivo2){
        int n;
        arquivo >> n;
        int vet[n];
        bool vet1[n];
        for(int i=0;i<n;i++){
            arquivo >> vet[i];
            vet1[i]=true;
        } 
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(vet[j]==vet[i] and j!=i){
                    vet1[i]=false;
                    vet1[j]=true;
                }
            }
        }
        for(int i=0;i<n;i++){
            if(vet1[i]==true){
                arquivo2 << vet[i] <<" ";
            }
        }
    }
    return 0;
}
        
