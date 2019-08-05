#include <iostream>

typedef float Dado;

// Criando a classe

class Vetor {

    public:
       Vetor(unsigned capacidade);
       ~Vetor();
       void Alterar(unsigned pos, Dado valor);
       float ProdutoInterno(Vetor V);
       
    protected:
       unsigned mCapacidade;
       unsigned mTamanho;
       Dado* mVetorDad;
};

using namespace std;

//Construtor

Vetor::Vetor(unsigned capacidade)
    :mCapacidade(capacidade), mTamanho(capacidade), 
     mVetorDad(new Dado[capacidade]){

    for (unsigned i = 0; i < capacidade; ++i)
    {
        mVetorDad[i] = 0;
    }
}

//Destrutor

Vetor:: ~Vetor()
{
    delete[] mVetorDad;
}

//Função Alterar

void Vetor::Alterar(unsigned pos, Dado valor)
{
    mVetorDad[pos] = valor;
}

float Vetor::ProdutoInterno(Vetor V)
{
    return 0.0f;
}

int main()
{
    Vetor v1(10);
    
    unsigned tamanho;
    cin >> tamanho;
   
    Dado valor;
    
    for (unsigned i = 0; i < tamanho; ++i)
    {
        cin >> valor;
        v1.Alterar(i, valor);
    }

    Vetor v2(10);

    

    return 0;
}
