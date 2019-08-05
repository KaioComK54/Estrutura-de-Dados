#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class Heap {
    private:
        Dado* Dados;
        unsigned Tamanho;
        unsigned Capacidade;
    public:
        Heap(Dado cap);
        ~Heap();
        void InsereHeap(Dado valor);
        void Remover();
        void CorrigeDescendo(unsigned i);
        void CorrigeSubindo(unsigned i);
        unsigned Pai(unsigned i);
        unsigned FilhoEsquerda(unsigned i);
        unsigned FilhoDireita(unsigned i);
        void Escrever();
};

Heap::Heap(Dado cap){
    Dados = new Dado[cap];
    Capacidade = cap;
    Tamanho = 0;
}

Heap::~Heap(){
    delete[] Dados;
}

void Heap::InsereHeap(Dado valor){
    if(Tamanho == Capacidade){
        cerr << "Heap cheio" << endl;
    }else{
        Dados[Tamanho] = valor;
        unsigned pos = Tamanho;
        CorrigeSubindo(pos);
        Tamanho++;
    }
}

void Heap::Remover(){
    if(Tamanho < 1){
        cerr << "Heap Vazio" << endl;
    }else{
        cout << "Item Removido: " << Dados[0] << endl;
        swap(Dados[0],Dados[Tamanho-1]);
        Tamanho--;
        CorrigeDescendo(0);
    }
}

void Heap::CorrigeDescendo(unsigned i){
    unsigned Esquerdo = FilhoEsquerda(i);
    unsigned Direito = FilhoDireita(i);
    unsigned maior = i;
    if(Esquerdo <= Tamanho-1 and Dados[Esquerdo] < Dados[i]){
        maior = Esquerdo;
    }
    if(Direito <= Tamanho-1 and Dados[Direito] < Dados[i]){
        maior = Direito;
    }
    if(maior != i){
        swap(Dados[i],Dados[maior]);
        CorrigeDescendo(maior);
    }
}

void Heap::CorrigeSubindo(unsigned i){
    unsigned pai = Pai(i);
    if(i >= 0 and Dados[pai] > Dados[i]){
        swap(Dados[i],Dados[pai]);
        CorrigeSubindo(pai);
    }
}

unsigned Heap::Pai(unsigned i){
    return (i-1)/2;
}

unsigned Heap::FilhoEsquerda(unsigned i){
    return (2*i)+1;
}

unsigned Heap::FilhoDireita(unsigned i){
    return (2*i)+2;
}

void Heap::Escrever(){
    for(unsigned i = 0;i < Tamanho;i++){
        cout << Dados[i] <<" ";
    }
}

int main(){
    Heap teste(10);
    char opcao;
    Dado valor;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                teste.InsereHeap(valor);
                break;
            case 'r':
                teste.Remover();
                cout << endl;
                teste.Escrever();
                cout << endl;
                break;
            case 'e':
                teste.Escrever();
                cout << endl;
                break;
            }
        }while(opcao != 'f');
    return 0;
}

                
        
