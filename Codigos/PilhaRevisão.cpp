#include <iostream>

using namespace std;

class Noh {
    friend class Pilha;
    private:
        Noh* Proximo;
        int Valor;
    public:
        Noh(int valor);
};

Noh::Noh(int valor){
    Proximo = NULL;
    Valor = valor;
}


class Pilha {
    private:
        Noh* Topo;
        int Tamanho;
    public:
        Pilha();
        ~Pilha();
        void Empilhar(int valor);
        void Desempilha();
        void EspiaTopo();
        void EscreverNoFinal();
};

Pilha::Pilha(){
    Topo = NULL;
    Tamanho = 0;
}

Pilha::~Pilha(){
    Noh* atual = Topo;
    Noh* anterior = NULL;
    while(atual != NULL){
        anterior = atual;
        atual = atual->Proximo;
        Topo = atual;
        delete anterior;
        Tamanho--;
    }
}

void Pilha::Empilhar(int valor){
    Noh* novo = new Noh(valor);
    if(Topo == NULL){
        Topo = novo;
    }else{
        novo->Proximo = Topo;
        Topo = novo;
    }
    Tamanho++;
}

void Pilha::Desempilha(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
    }else{
        Noh* aux = Topo;
        Topo = aux->Proximo;
        delete aux;
        Tamanho--;
    }
}

void Pilha::EspiaTopo(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
    }else{
        std::cout << Topo->Valor;
    }
}

void Pilha::EscreverNoFinal(){
    while(Tamanho != 0){
        EspiaTopo();
        cout <<" ";
        Desempilha();
    }
}

int main(){
    Pilha teste;
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                teste.Empilhar(valor);
                break;
            case 'r':
                teste.Desempilha();
                break;
            case 't':
                teste.EspiaTopo();
                cout << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    teste.EscreverNoFinal();
    return 0;
}
                

