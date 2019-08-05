#include <iostream>
#include <cstdlib>

using namespace std;

struct Aluno{
    string nome;
    float media;
    int faltas;
};

int main(){
    int n;
    cin >> n;
    Aluno *dados=new Aluno[n];
    for(int i=0;i<n;i++){
        cin >> dados[i].nome;
        cin >> dados[i].media;
        cin >> dados[i].faltas;
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(dados[i].media < dados[j].media){
                swap(dados[i].nome,dados[j].nome);
                swap(dados[i].media,dados[j].media);
                swap(dados[i].faltas,dados[j].faltas);
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << dados[i].nome << endl;
    }
    delete[] dados;
    return 0;
}
                
        
