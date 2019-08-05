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
        int FilhoEsquerdo(int i);
        int FilhoDireito(int i);
        void CorrigeDescendo(int i);
        void CorrigeSubindo(int i);
        void Escreve();
};

Heap::Heap(int cap){
    Dados = new int[cap];
    Capacidade = cap;
    Tamanho = 0;
}

Heap::~Heap(){
    delete[] Dados;
}

void Heap::Inserir(int valor){
    if(Tamanho == Capacidade){
        cerr << "Heap Cheio" << endl;
    }else{
        Dados[Tamanho] = valor;
        int pos = Tamanho;
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

int Heap::Pai(int i){
    return (i-1)/2;
}

int Heap::FilhoEsquerdo(int i){
    return (2*i)+1;
}

int Heap::FilhoDireito(int i){
    return (2*i)+2;
}

void Heap::CorrigeDescendo(int i){
    int Esq = FilhoEsquerdo(i);
    int Dir = FilhoDireito(i);
    int Menor = i;
    if(Esq <= Tamanho-1 and Dados[Esq] < Dados[i]){
        Menor = Esq;
    }
    if(Dir <= Tamanho-1 and Dados[Dir] < Dados[Menor]){
        Menor = Dir;
    }
    if(Menor != i){
        swap(Dados[i],Dados[Menor]);
        CorrigeDescendo(Menor);
    }
}

void Heap::CorrigeSubindo(int i){
    int pai = Pai(i);
    if(i >= 0 and Dados[pai] > Dados[i]){
        swap(Dados[i],Dados[pai]);
        CorrigeSubindo(pai);
    }
}

void Heap::Escreve(){
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
                Teste.Escreve();
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}
