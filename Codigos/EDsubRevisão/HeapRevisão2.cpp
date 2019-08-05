#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

class Heap {
    private:
        Dado* Dados;
        Dado Tamanho;
        Dado Capacidade;
    public:
        Heap(int cap);
        ~Heap();
        void Inserir(Dado valor);
        void Remover();
        Dado Pai(Dado i);
        Dado FilhoDireito(Dado i);
        Dado FilhoEsquerdo(Dado i);
        void CorrigeDescendo(Dado i);
        void CorrigeSubindo(Dado i);
        void Escrever();
};

Heap::Heap(int cap){
    Dados = new Dado[cap];
    Capacidade = cap;
    Tamanho = 0;
}

Heap::~Heap(){
    delete[] Dados;
}

void Heap::Inserir(Dado valor){
    if(Tamanho == Capacidade){
        cerr << "Heap Cheio" << endl;
    }else{
        Dados[Tamanho] = valor;
        Dado pos = Tamanho;
        CorrigeSubindo(pos);
        Tamanho++;
    }
}

void Heap::Remover(){
    if(Tamanho == 0){
        cerr << "Heap Vazio" << endl;
    }else{
        cout << "Item Removido : " << Dados[0] << endl;
        swap(Dados[0],Dados[Tamanho-1]);
        Tamanho--;
        CorrigeDescendo(0);
    }
}

Dado Heap::Pai(Dado i){
    return (i-1)/2;
}

Dado Heap::FilhoEsquerdo(Dado i){
    return (2*i)+1;
}

Dado Heap::FilhoDireito(Dado i){
    return (2*i)+2;
}

void Heap::CorrigeDescendo(Dado i){
    Dado Esq = FilhoEsquerdo(i);
    Dado Dir = FilhoDireito(i);
    Dado maior = i;
    if(Esq <= Tamanho-1 and Dados[Esq] > Dados[i]){
        maior = Esq;
    }
    if(Dir <= Tamanho-1 and Dados[Dir] > Dados[i]){
        maior = Dir;
    }
    if(maior != i){
        swap(Dados[i],Dados[maior]);
        CorrigeDescendo(maior);
    }
}

void Heap::CorrigeSubindo(Dado i){
    Dado pai = Pai(i);
    if(i >= 0 and Dados[pai] < Dados[i]){
        swap(Dados[i],Dados[pai]);
        CorrigeSubindo(pai);
    }
}

void Heap::Escrever(){
    for(Dado i = 0;i < Tamanho;i++){
        cout << Dados[i] <<" ";
    }
}

int main(){
    Heap teste(20);
    Dado valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                teste.Inserir(valor);
                break;
            case 'r':
                teste.Remover();
                break;
            case 'e':
                teste.Escrever();
                cout << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}


