#include <iostream>

using namespace std;

typedef int Dado;


class fila{
    private:
        Dado* mVetor;
        Dado mTamanho;
        Dado mCapacidade;
    public:
        fila(Dado cap);
        ~fila();
        void imprime();
};

fila::fila(Dado cap){
    mCapacidade = cap;
    mTamanho = 0;
    mVetor = new Dado(mCapacidade);
    for(Dado i =0;i<mCapacidade;i++){
        
        ++mTamanho;
    }
}

fila::~fila(){
    delete[] mVetor;
}

void fila::imprime(){
    cout <<"Capacidade:"<<" "<< mCapacidade <<" ";
    cout <<"Tamanho:"<<" "<< mTamanho << endl;
    for(Dado i=0;i<mTamanho;++i){
        cout << mVetor[i] <<" ";
    }
}

int main(){
    Dado tam;
    cin >> tam;
    fila vetor1(tam);
    vetor1.imprime();
    return 0;
}
        

