#include <iostream>

typedef unsigned Dado;


class Vetor {

    public:
       Vetor(unsigned capacidade);
       ~Vetor();
       void Alterar(unsigned pos, Dado valor);
       void Escrever(unsigned capacidade);
       int ProdutoInterno(Vetor V);
       int Busca(unsigned capacidade,unsigned elemento);
       void Ordenacao(unsigned capacidade);
       
    protected:
       unsigned mCapacidade;
       unsigned mTamanho;
       Dado* mVetorDados;
};

using namespace std;

//Construtor

Vetor::Vetor(unsigned capacidade)
    :mCapacidade(capacidade), mTamanho(capacidade), 
     mVetorDados(new Dado[capacidade]){

    for (unsigned i = 0; i < capacidade; ++i)
    {
        mVetorDados[i] = 0;
    }
}


Vetor:: ~Vetor()
{
    delete[] mVetorDados;
}


void Vetor::Alterar(unsigned pos, Dado valor)
{
    mVetorDados[pos] = valor;
}
void Vetor::Escrever(unsigned capacidade){
    for(unsigned i=0;i<capacidade;i++){
        cout << mVetorDados[i] <<" ";
    }
}

int Vetor::ProdutoInterno(Vetor V)
{
    return 0.0f;
}

int Vetor::Busca(unsigned capacidade,unsigned elemento){
    unsigned aux=0;
    for(unsigned i=0;i<capacidade;i++){
        if(mVetorDados[i]==elemento){
            aux=mVetorDados[i];
        }
    }
    return aux;
}

void Vetor::Ordenacao(unsigned capacidade){
    unsigned aux=0;
    for(unsigned i=0;i<capacidade;i++){
        for(unsigned j=i+1;j<capacidade;j++){
            if(mVetorDados[i]>mVetorDados[j]){
                aux=mVetorDados[i];
                mVetorDados[i]=mVetorDados[j];
                mVetorDados[j]=aux;
            }
        }
    }
}
        

int main()
{    
    unsigned tamanho;
    cin >> tamanho;
    Vetor v1(tamanho);
    Dado valor;
    
    for (unsigned i = 0; i < tamanho; ++i)
    {
        cin >> valor;
        v1.Alterar(i, valor);
    }
    v1.Ordenacao(tamanho);
    v1.Escrever(tamanho);
    unsigned elemento;
    cin >> elemento;
    cout << v1.Busca(tamanho,elemento);
    return 0;
}
