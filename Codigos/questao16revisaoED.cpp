#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream arquivo("entrada.txt");
    ofstream arquivo2("saida.txt");
    int vet[100];
    int qtd=0;
    int valor;
    if(arquivo and arquivo2){
        while(arquivo >> valor){
            vet[qtd]=valor;
            qtd++;
        }
        for(int i=qtd-1;i>=0;i--){
                arquivo2 << vet[i] <<" ";
        }
    }
    return 0;
}
