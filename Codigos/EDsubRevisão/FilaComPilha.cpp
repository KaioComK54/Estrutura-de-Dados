#include <iostream>

using namespace std;

class Noh{
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

class Fila{
    private:
        Noh* Primeiro;
        Noh* Ultimo;
        int Tamanho;
    public:
        Fila();
        ~Fila();
        void Enfileira(int valor);
        int Desenfileira();
        int Desempilha();
        int RetornaTamanho();
        bool VerificaFila();
};

Fila::Fila(){
    Primeiro = NULL;
    Ultimo = NULL;
    Tamanho = 0;
}

Fila::~Fila(){
    Noh* atual = Primeiro;
    while(atual != NULL){
        Noh* anterior = atual;
        atual = atual->Proximo;
        delete anterior;
        Tamanho--;
    }
    Primeiro = NULL;
    Ultimo = NULL;
}

void Fila::Enfileira(int valor){
    if(Tamanho == 0){
        Noh* novo = new Noh(valor);
        Primeiro = novo;
        Ultimo = novo;
        Tamanho++;
    }else{
        Noh* novo = new Noh(valor);
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
        Noh* atual = Primeiro;
        int valor = Primeiro->Valor;
        Primeiro = Primeiro->Proximo;
        delete atual;
        Tamanho--;
        return valor;
    }
}

int Fila::Desempilha(){
    if(Tamanho == 0){
        cerr << "Fila Vazia" << endl;
        return 0;
    }else{
        Fila* A = new Fila();
        Fila* B  = new Fila();
        int TamAux = Tamanho-1;
        while(Tamanho > 1){
            int dado = Desenfileira();
            B->Enfileira(dado);
        }
        int dado = Desenfileira();
        A->Enfileira(dado);
        int i = TamAux;
        while(i > 0){
            int dado = B->Desenfileira();
            A->Enfileira(dado);
            i--;
        }
        int Retorno = A->Desenfileira();
        while(TamAux > 0){
            int dado = A->Desenfileira();
            Enfileira(dado);
            TamAux--;
        }
        return Retorno;
    }
}


int Fila::RetornaTamanho(){
    return Tamanho;
}

bool Fila::VerificaFila(){
    if(Tamanho == 0){
        return false;
    }
    return true;
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
            case 'd':
                cout << Teste.Desempilha() << endl;
                break;
            case 't':
                cout << Teste.RetornaTamanho() << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}

