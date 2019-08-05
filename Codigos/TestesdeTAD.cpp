#include <iostream>

typedef unsigned Dado;


class Vetor {
    
    public:
       Vetor(unsigned capacidade);
       ~Vetor();
       void Alterar(unsigned pos, Dado valor);
       void Escrever(unsigned capacidade);
       int ProdutoInterno(Vetor V);
       void Busca(unsigned capacidade,unsigned elemento);
       void Ordenacao(unsigned capacidade);
       void Remover(unsigned capacidade,unsigned *vetor,unsigned tamanho);
       void ProdutoValor(unsigned capacidade,unsigned variavel);
       void RemoverDuplicado(unsigned capacidade);
       int mValor;
       
    protected:
       unsigned mCapacidade;
       unsigned mTamanho;
       Dado* mVetorDados;
};

using namespace std;



Vetor::Vetor(unsigned capacidade)
    :mCapacidade(capacidade), mTamanho(capacidade), 
     mVetorDados(new Dado[capacidade])){
    for (unsigned i = 0; i < capacidade; ++i)
    {
        cin >> mVetorDados[i];
    }
     mValor=10;
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
    cout << endl;
    cout << mCapacidade <<" "<< mTamanho;
}

int Vetor::ProdutoInterno(Vetor V){
    return 0.0f;
}

void Vetor::Busca(unsigned capacidade,unsigned elemento){
    for(unsigned i=0;i<capacidade;i++){
        if(mVetorDados[i]==elemento){
            cout << i <<" ";
        }
    }
}

void Vetor::Remover(unsigned capacidade,unsigned *vetor,unsigned tamanho){
    for(unsigned i=0;i<capacidade;i++){
        for(unsigned j=0;j<tamanho;j++){
        }
    }
}

void Vetor::Ordenacao(unsigned capacidade){
    unsigned aux=0;
    for(unsigned i=0;i<capacidade;i++){
        for(unsigned j=i+1;j<capacidade;j++){
            if((mVetorDados[i]>mVetorDados[j])){
                aux=mVetorDados[i];
                mVetorDados[i]=mVetorDados[j];
                mVetorDados[j]=aux;
            }
        }
    }
}
 
void Vetor::ProdutoValor(unsigned capacidade,unsigned variavel){
    for(unsigned i=0;i<capacidade;i++){
        mVetorDados[i]=mVetorDados[i]*variavel;
        cout << mVetorDados[i] <<" ";
    }
}

void Vetor::RemoverDuplicado(unsigned capacidade){
    unsigned pos=0;
    unsigned valor=0;
    for(unsigned i=0;i<capacidade;i++){
        pos=i;
        valor=mVetorDados[i];
        for(unsigned j=0;j<capacidade;j++){
            if(mVetorDados[j]==valor and j!=pos){
                mVetor[j]=false;
            }
        }
        pos=0;
        valor=0;
    }
}
        
    
     

int main(){    
    unsigned tamanho;
    cin >> tamanho;
    Vetor v1(tamanho);
    v1.Ordenacao(tamanho);
    v1.Escrever(tamanho);
    unsigned termo;
    cin >> termo;
    v1.ProdutoValor(tamanho,termo);
    cout << endl;
    v1.RemoverDuplicado(tamanho);
    v1.Escrever(tamanho);
    cout << endl;
    return 0;
}
