#include <iostream>

using namespace std;

class Heap{
    private:
        int* Dados;
        int Tamanho;
        int Capacidade;
    public:
        Heap(int cap);
        ~Heap();
        void Inserir(int valor);
        void Remover();
        int Pai(int i);
        int FilhoDireito(int i);
        int FilhoEsquerdo(int i);
        void CorrigeDescendo(int i);
        void CorrigeSubindo(int i);
        void Escrever();
};

Heap::Heap(int cap){
    Dados = new int[cap];
    Tamanho = 0;
    Capacidade = cap;
}

Heap::~Heap(){
    delete[] Dados;
}

void Heap::Inserir(int valor){
    if(Tamanho == Capacidade){
        cerr << "Heap Cheio" << endl;
    }else{
        Dados[Tamanho] = valor;
        int Pos = Tamanho;
        CorrigeSubindo(Pos);
        Tamanho++;
    }
}

void Heap::Remover(){
    if(Tamanho == 0){
        cerr << "Heap Vazio" << endl;
    }else{
        cout << "Item Removido : "<< Dados[0] << endl;
        swap(Dados[0],Dados[Tamanho-1]);
        Tamanho--;
        CorrigeDescendo(0);
    }
}

int Heap::Pai(int i){
    return (i-1)/2;
}

int Heap::FilhoDireito(int i){
    return (2*i)+2;
}

int Heap::FilhoEsquerdo(int i){
    return (2*i)+1;
}

void Heap::CorrigeDescendo(int i){
    int Esq = FilhoEsquerdo(i);
    int Dir = FilhoDireito(i);
    int Maior = i;
    if(Esq <= Tamanho-1 and Dados[Esq] > Dados[i]){
        Maior = Esq;
    }
    if(Dir <= Tamanho-1 and Dados[Dir] > Dados[Maior]){
        Maior = Dir;
    }  
    if(Maior != i){
        swap(Dados[i],Dados[Maior]);
        CorrigeDescendo(Maior);
    }
}

void Heap::CorrigeSubindo(int i){
    int pai = Pai(i);
    if(i >= 0 and Dados[pai] > Dados[i]){
        swap(Dados[i],Dados[pai]);
        CorrigeSubindo(pai);
    }
}

void Heap::Escrever(){
    for(int i = 0;i < Tamanho;i++){
        cout << Dados[i] <<" ";
    }
    cout << endl;
}

int main(){
    Heap Teste(15);
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                Teste.Inserir(valor);
                break;
            case 'r':
                Teste.Remover();
                break;
            case 'e':
                Teste.Escrever();
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}
