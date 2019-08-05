#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream arquivo("palavras.txt");
    ifstream arquivo2("numeros.txt");
    ofstream arquivo3("frase.txt");
    if(arquivo and arquivo2 and arquivo3){
        int qtd=0;
        string words[50];
        string texto;
        while(arquivo >> texto ){
            words[qtd]=texto;
            qtd++;
        }
        int valor;
        while(arquivo2 >> valor){
            arquivo3 << words[valor-1] <<" ";
        }
    }
    return 0;
}
            

