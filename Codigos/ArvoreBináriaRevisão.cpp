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


class ABB {
    private:
        Noh* Raiz;
        Noh* MinimoAux(Noh* aux);
        Noh* BuscaAux(int valor);
        void Transplanta(Noh* antigo, Noh* novo);
        void PercorreEmOrdemAux(Noh* aux);
        void PercorreEmPosOrdemAux(Noh* aux);
        void PercorreEmPreOrdemAux(Noh* aux);
    public:
        ABB();
        ~ABB();
        void Inserir(int valor);
        void Remover(int valor);
        void PercorreEmOrdem();
        void PercorreEmPreOrdem();
        void PercorreEmPosOrdem();
};

ABB::ABB(){
    Raiz = NULL;
}

ABB::~ABB(){
    delete Raiz;
}

Noh* ABB::MinimoAux(Noh* aux){
    while(aux->FilhoEsquerdo != NULL){
        aux = aux->FilhoEsquerdo;
    }
    return aux;
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

void ABB::Transplanta(Noh* antigo,Noh* novo){
    if(antigo == Raiz){
        Raiz = novo;
    }else{
        if(antigo == antigo->Pai->FilhoDireito){
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
    Noh* remove = BuscaAux(valor);
    if(remove == NULL){
        cerr << "Nao Encontrado" << endl;
    }else{
        if(remove->FilhoDireito == NULL){
            Transplanta(remove,remove->FilhoEsquerdo);
        }else if(remove->FilhoEsquerdo == NULL){
            Transplanta(remove,remove->FilhoDireito);
        }else if(remove->FilhoDireito != NULL and remove->FilhoEsquerdo!= NULL){
            Noh* sucessor = MinimoAux(remove->FilhoDireito);
            if(sucessor->Pai != remove){
                Transplanta(sucessor,sucessor->FilhoDireito);
                sucessor->FilhoDireito = remove->FilhoDireito;
                sucessor->FilhoDireito->Pai = sucessor;
            }
            Transplanta(remove,sucessor);
            sucessor->FilhoEsquerdo = remove->FilhoEsquerdo;
            sucessor->FilhoEsquerdo->Pai = sucessor;
        }
        remove->FilhoDireito = NULL;
        remove->FilhoEsquerdo = NULL;
        delete remove;
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
            case 'p':
                teste.PercorreEmPreOrdem();
                cout << endl;
                break;
            case 'o':
                teste.PercorreEmOrdem();
                cout << endl;
                break;
            case 'd':
                teste.PercorreEmPosOrdem();
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

        



