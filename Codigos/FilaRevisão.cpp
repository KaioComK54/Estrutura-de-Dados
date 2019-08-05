#include <iostream>

using namespace std;

class Noh {
    friend class Fila;
    private:
        Noh* Proximo;
        int Valor;
    public:
        Noh(int dado);
};

Noh::Noh(int dado){
    Proximo = NULL;
    Valor = dado;
}

class Fila {
    private:
        Noh* Primeiro;
        Noh* Ultimo;
        int Tamanho;
    public:
        Fila();
        ~Fila();
        void Enfileira(int valor);
        int Desenfileira();
        int RetornaTamanho();
        int RetornaPrimeiro();
};

Fila::Fila(){
    Primeiro = NULL;
    Ultimo = NULL;
    Tamanho = 0;
}

Fila::~Fila(){
    while(Tamanho != 0){
        Noh* aux = Primeiro;
        Primeiro = Primeiro->Proximo;
        delete aux;
        Tamanho--;
    }
    Primeiro = NULL;
    Ultimo = NULL;
}

void Fila::Enfileira(int valor){
    Noh* novo = new Noh(valor);
    if(Tamanho == 0){
        Primeiro = novo;
        Ultimo = novo;
        Tamanho++;
    }else{
        Ultimo->Proximo = novo;
        Ultimo = novo;
        Tamanho++;
    }
}

int Fila::Desenfileira(){
    if(Tamanho == 0){
        cerr << "Fila Vazia" << endl;
        return 0;
    }else{
        int valor = Primeiro->Valor;
        Noh* aux = Primeiro;
        Primeiro = Primeiro->Proximo;
        delete aux;
        Tamanho--;
        return valor;
    }
}

int Fila::RetornaPrimeiro(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
        return 0;
    }else{
        return Primeiro->Valor;
    }
}

int Fila::RetornaTamanho(){
    return Tamanho;
}

int main(){
    Fila Teste;
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                Teste.Enfileira(valor);
                break;
            case 'r':
                cout << Teste.Desenfileira() << endl;
                break;
            case 't':
                cout << Teste.RetornaTamanho() << endl;
                break;
            case 'p':
                cout << Teste.RetornaPrimeiro() << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}
