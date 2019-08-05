#include <fstream>
#include <iostream>

using namespace std;

int main(){
    ifstream arquivo("Meu_Arquivo.txt");
    string palavra;
    int aux=0;
    int qtd;
    if(arquivo){
        while(arquivo >> palavra){
            qtd=palavra.size();
            for(int i=0;i<qtd;i++){
                if(palavra[i]!='\0'){
                    aux++;
                }
            }
        }
    }
    cout << aux;
    return 0;
}
            
