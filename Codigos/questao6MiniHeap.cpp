
#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;


class Heap{
    private:
       Dado* dados;
       Dado Capacidade;
       Dado Tamanho;
    public:
       Heap(Dado vetor[],Dado tam);
       ~Heap();
       Dado Esquerdo(Dado pos);
       Dado Direito(Dado pos);
       Dado Pai(Dado pos);
       void RetiraRaiz();
       void CorrigeDescendo(Dado pos);
       void Escreve();
       void Troca(Dado* valor1,Dado* valor2);
       void Correcao();
};

Heap::Heap(Dado* vetor,Dado tam){
    Capacidade = tam;
    Tamanho = tam;
    dados = new Dado[Capacidade];
    for(Dado i=0;i<Tamanho;i++){
        dados[i] = vetor[i];
    }
};

Heap::~Heap(){
    delete[] dados;
    Tamanho = 0;
};

Dado Heap::Esquerdo(Dado pos){
    return (2*pos+1);
}

Dado Heap::Direito(Dado pos){
    return (2*pos+2);
}

Dado Heap::Pai(Dado pos){
    return ((pos-1)/2);
}

void Heap::RetiraRaiz(){
    if(Tamanho < 1){
        cerr << "Erro" << endl;
    }else{
        swap(dados[0],dados[Tamanho-1]);
        Tamanho--;
        Dado inicio = 0;
        CorrigeDescendo(inicio);
    }
}

void Heap::CorrigeDescendo(Dado pos){
    Dado esq = Esquerdo(pos);
    Dado dir = Direito(pos);
    Dado menor = pos;
    if((esq < Tamanho)and(dados[esq] < dados[pos])){
        menor = esq;
    }
    if((dir < Tamanho)and(dados[dir] < dados[menor])){
        menor = dir;
    }
    if(menor != pos){
        Troca(&dados[pos],&dados[menor]);
        CorrigeDescendo(menor);
    }
}

void Heap::Troca(Dado* valor1,Dado* valor2){
    Dado temp = *valor1;
    *valor1 = *valor2;
    *valor2 = temp;
}

void Heap::Escreve(){
    for(Dado i = 0;i < Tamanho;i++){
        cout << dados[i] <<" ";
    }
    cout << endl;
}

void Heap::Correcao(){
    for(Dado i=(Tamanho-1)/2;i>=0;i--){
        Dado esq = Esquerdo(i);
        Dado dir = Direito(i);
        if(dados[esq] < dados[i] or dados[dir] < dados[i] or (dados[esq] < dados[i] and dados[dir] < dados[i])){
            CorrigeDescendo(i);
            cout << i <<':'<<" ";
            Escreve();
        }
    }
}

int main(){
    Dado tam;
    cin >> tam;
    Dado vetor[tam];
    for(Dado i=0;i<tam;i++){
        cin >> vetor[i];
    }
    cout << endl;
    Heap* vet = new Heap(vetor,tam);
    vet->Correcao();
    return 0;
}
    
