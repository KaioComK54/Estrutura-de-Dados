#include <iostream>

using namespace std;

class Noh {
    friend class ABB;
    private:
        Noh* Pai;
        Noh* FilhoDireito;
        Noh* FilhoEsquerdo;
        int Chave;
    public:
        Noh(int valor);
        ~Noh();
};

Noh::Noh(int valor){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Chave = valor;
}

Noh::~Noh(){
    delete FilhoEsquerdo;
    delete FilhoDireito;
}

class ABB{
    private:
        Noh* Raiz;
        Noh* BuscaAux(int valor);
        Noh* MinimoAux(Noh* aux);
        void Transplanta(Noh* antigo,Noh* novo);
        void PercorreEmOrdemAux(Noh* aux);
        void PercorreEmPosOrdemAux(Noh* aux);
        void PercorreEmPreOrdemAux(Noh* aux);
        void AlturaAux(int& AlturaNoh,Noh* aux,int nivel);
    public:
        ABB();
        ~ABB();
        void Inserir(int valor);
        void Remover(int valor);
        void PercorreEmOrdem();
        void PercorreEmPosOrdem();
        void PercorreEmPreOrdem();
        int Altura();
};

ABB::ABB(){
    Raiz = NULL;
}

ABB::~ABB(){
    delete Raiz;
}

Noh* ABB::BuscaAux(int valor){
    Noh* atual = Raiz;
    while(atual != NULL){
        if(atual->Chave == valor){
            return atual;
        }else{
            if(atual->Chave > valor){
                atual = atual->FilhoEsquerdo;
            }else{
                atual = atual->FilhoDireito;
            }
        }
    }
    return atual;
}

Noh* ABB::MinimoAux(Noh* aux){
    while(aux->FilhoEsquerdo != NULL){
        aux = aux->FilhoEsquerdo;
    }
    return aux;
}

void ABB::Transplanta(Noh* antigo,Noh* novo){
    if(antigo == Raiz){
        Raiz = novo;
    }else{
        if(antigo->Pai->FilhoDireito == antigo){
            antigo->Pai->FilhoDireito = novo;
        }else{
            antigo->Pai->FilhoEsquerdo = novo;
        }
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}

void ABB::PercorreEmOrdemAux(Noh* aux){
    if(aux != NULL){
        PercorreEmOrdemAux(aux->FilhoEsquerdo);
        cout << aux->Chave <<" ";
        PercorreEmOrdemAux(aux->FilhoDireito);
    }
}

void ABB::PercorreEmPosOrdemAux(Noh* aux){
    if(aux != NULL){
        PercorreEmPosOrdemAux(aux->FilhoEsquerdo);
        PercorreEmPosOrdemAux(aux->FilhoDireito);
        cout << aux->Chave <<" ";
    }
}

void ABB::PercorreEmPreOrdemAux(Noh* aux){
    if(aux != NULL){
        cout << aux->Chave <<" ";
        PercorreEmPreOrdemAux(aux->FilhoEsquerdo);
        PercorreEmPreOrdemAux(aux->FilhoDireito);
    }
}

void ABB::Inserir(int valor){
    Noh* novo = new Noh(valor);
    if(Raiz == NULL){
        Raiz = novo;
    }else{
        Noh* atual = Raiz;
        Noh* anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(atual->Chave > valor){
                atual = atual->FilhoEsquerdo;
            }else{
                atual = atual->FilhoDireito;
            }
        }
        novo->Pai = anterior;
        if(anterior->Chave > novo->Chave){
            anterior->FilhoEsquerdo = novo;
        }else{
            anterior->FilhoDireito = novo;
        }
    }
}

void ABB::Remover(int valor){
    Noh* remover = BuscaAux(valor);
    if(remover == NULL){
        cerr << "Nao Encontrado" << endl;
    }else{
        if(remover->FilhoDireito == NULL){
            Transplanta(remover,remover->FilhoEsquerdo);
        }else if(remover->FilhoEsquerdo == NULL){
            Transplanta(remover,remover->FilhoDireito);
        }else{
            Noh* sucessor = MinimoAux(remover->FilhoDireito);
            if(sucessor->Pai != remover){
                Transplanta(sucessor,sucessor->FilhoDireito);
                sucessor->FilhoDireito = remover->FilhoDireito;
                sucessor->FilhoDireito->Pai = sucessor;
            }
            Transplanta(remover,sucessor);
            sucessor->FilhoEsquerdo = remover->FilhoEsquerdo;
            sucessor->FilhoEsquerdo->Pai = sucessor;
        }
        remover->FilhoDireito = NULL;
        remover->FilhoEsquerdo = NULL;
        delete remover;
    }
}

void ABB::PercorreEmOrdem(){
    PercorreEmOrdemAux(Raiz);
}

void ABB::PercorreEmPosOrdem(){
    PercorreEmPosOrdemAux(Raiz);
}

void ABB::PercorreEmPreOrdem(){
    PercorreEmPreOrdemAux(Raiz);
}

int ABB::Altura(){
    int AlturaNoh = 0;
    int nivel = 0;
    AlturaAux(AlturaNoh,Raiz,nivel);
    return AlturaNoh;
}

void ABB::AlturaAux(int& AlturaNoh,Noh* aux,int nivel){
    if(aux != NULL){
        AlturaAux(AlturaNoh,aux->FilhoEsquerdo,nivel+1);
        AlturaAux(AlturaNoh,aux->FilhoDireito,nivel+1);
    }
    if(nivel > AlturaNoh){
        AlturaNoh = nivel-1;
    }
}

int main(){
    ABB teste;
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                teste.Inserir(valor);
                break;
            case 'r':
                cin >> valor;
                teste.Remover(valor);
                break;
            case 'o':
                teste.PercorreEmOrdem();
                cout << endl;
                break;
            case 'p':
                teste.PercorreEmPreOrdem();
                cout << endl;
                break;
            case 's':
                teste.PercorreEmPosOrdem();
                cout << endl;
                break;
            case 'a':
                cout << teste.Altura() << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}



