#include <iostream>

using namespace std;

class Noh{
    friend class ABB;
    private:
        Noh* Pai;
        Noh* FilhoDireito;
        Noh* FilhoEsquerdo;
        int Chave;
    public:
        Noh(int chave);
};

Noh::Noh(int chave){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Chave = chave;
}

class ABB{
    private:
        Noh* Raiz;
        Noh* BuscaAux(int valor);
        Noh* MinimoAux(Noh* aux);
        void PercorreEmOrdem(Noh* aux);
        void Transplanta(Noh* antigo,Noh* novo);
        void PercorreEmPreOrdem(Noh* aux);
        void PercorreEmPosOrdem(Noh* aux);
        void Destrucao(Noh* aux);
    public:
        ABB();
        ~ABB();
        void Inserir(int chave);
        void Remover(int chave);
        void PreOrdem();
        void PosOrdem();
        void Ordem();
};

ABB::ABB(){
    Raiz = NULL;
}

ABB::~ABB(){
    Destrucao(Raiz);
}

Noh* ABB::BuscaAux(int valor){
    Noh* atual = Raiz;
    while(atual != NULL){
        if(atual->Chave == valor){
            return atual;
        }else if(atual->Chave > valor){
            atual = atual->FilhoEsquerdo;
        }else{
            atual = atual->FilhoDireito;
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
    if(Raiz == antigo){
        Raiz = novo;
    }
    if(antigo == antigo->Pai->FilhoDireito){
        antigo->Pai->FilhoDireito = novo;
    }else{
        antigo->Pai->FilhoEsquerdo = novo;
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}

void ABB::PercorreEmOrdem(Noh* aux){
    if(aux != NULL){
        PercorreEmOrdem(aux->FilhoEsquerdo);
        cout << aux->Chave <<" ";
        PercorreEmOrdem(aux->FilhoDireito);
    }
}

void ABB::PercorreEmPosOrdem(Noh* aux){
    if(aux != NULL){
        PercorreEmPosOrdem(aux->FilhoEsquerdo);
        PercorreEmPosOrdem(aux->FilhoDireito);
        cout << aux->Chave <<" ";
    }
}

void ABB::PercorreEmPreOrdem(Noh* aux){
    if(aux != NULL){
        cout << aux->Chave <<" ";
        PercorreEmPreOrdem(aux->FilhoEsquerdo);
        PercorreEmPreOrdem(aux->FilhoDireito);
    }
}

void ABB::Inserir(int chave){
    Noh* novo = new Noh(chave);
    if(Raiz == NULL){
        Raiz = novo;
    }else{
        Noh* atual = Raiz;
        Noh* anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(atual->Chave > chave){
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

void ABB::Destrucao(Noh* aux){
    if(aux != NULL){
        Noh* atual = aux;
        Destrucao(aux->FilhoEsquerdo);
        Destrucao(aux->FilhoDireito);
        delete atual;
    }
}

void ABB::Remover(int chave){
    Noh* remover = BuscaAux(chave);
    if(Raiz == NULL or remover == NULL){
        cerr << "Erro na Remocao" << endl;
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

void ABB::PreOrdem(){
    PercorreEmPreOrdem(Raiz);
}

void ABB::PosOrdem(){
    PercorreEmPosOrdem(Raiz);
}

void ABB::Ordem(){
    PercorreEmOrdem(Raiz);
}

int main(){
    ABB Teste;
    int chave;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> chave;
                Teste.Inserir(chave);
                break;
            case 'r':
                cin >> chave;
                Teste.Remover(chave);
                break;
            case 'a':
                Teste.PreOrdem();
                cout << endl;
                break;
            case 'd':
                Teste.PosOrdem();
                cout << endl;
                break;
            case 'o':
                Teste.Ordem();
                cout << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}

                
    


    
