#include <iostream>

using namespace std;

class Noh{
    friend class Pilha;
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

class Pilha{
    private:
        Noh* Topo;
        int Tamanho;
        int DesempilhaAux(int& Retorno);
    public:
        Pilha();
        ~Pilha();
        void Empilhar(int valor);
        void Desempilha();
        void EspiaTopo();
        int EspiaTamanho();
        void EscreverNoFinal();
        void InvertePilha();
};

int Pilha::DesempilhaAux(int& Retorno){
    Noh* atual = Topo;
    Retorno = atual->Valor;
    Topo = atual->Proximo;
    delete atual;
    --Tamanho;
    return Retorno;
}

int Pilha::EspiaTamanho(){
    return Tamanho;
}

Pilha::Pilha(){
    Tamanho = 0;
    Topo = NULL;
}

Pilha::~Pilha(){
    Noh* aux = Topo;
    Noh* anterior = NULL;
    while(aux != NULL){
        anterior = aux;
        aux = aux->Proximo;
        Topo = aux;
        delete anterior;
        --Tamanho;
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
    ++Tamanho;
}

void Pilha::Desempilha(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
    }else{
        Noh* remover = Topo;
        Topo = remover->Proximo;
        delete remover;
        --Tamanho;
    }
}

void Pilha::EspiaTopo(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
    }else{
        cout << Topo->Valor;
    }
}

void Pilha::EscreverNoFinal(){
    if(Tamanho == 0){
        cerr << "Pilha Vazia" << endl;
    }else{
        while(Tamanho != 0){
            EspiaTopo();
            cout <<" ";
            Desempilha();
        }
    }
}

void Pilha::InvertePilha(){
    Pilha* A = new Pilha();
    while(Tamanho != 0){
        int Retorno = 0;
        DesempilhaAux(Retorno);
        A->Empilhar(Retorno);
    }
    Pilha* B = new Pilha();
    while(A->EspiaTamanho() != 0){
        int Retorno = 0;
        A->DesempilhaAux(Retorno);
        B->Empilhar(Retorno);
    }
    while(B->EspiaTamanho() != 0){
        int Retorno = 0;
        B->DesempilhaAux(Retorno);
        Empilhar(Retorno);
    }
}
        
    
int main(){
    Pilha Teste;
    int Valor;
    char Opcao;
    do{
        cin >> Opcao;
        switch(Opcao){
            case 'i':
                cin >> Valor;
                Teste.Empilhar(Valor);
                break;
            case 'r':
                Teste.Desempilha();
                break;
            case 'o':
                Teste.EspiaTopo();
                cout << endl;
                break;
            case 'e':
                Teste.EscreverNoFinal();
                break;
            case 'I':
                Teste.InvertePilha();
                break;
            case 't':
                cout << Teste.EspiaTamanho() << endl;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(Opcao != 'f');
    return 0;
}
   
