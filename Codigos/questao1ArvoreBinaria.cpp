#include <iostream>

using namespace std;

typedef int Dado;

class noh{
    friend class Arvore;
    private:
      noh* Pai;
      noh* FilhoEsquerdo;
      noh* FilhoDireito;
      Dado Chave;
    public:
      noh(const Dado& valor);
};

noh ::noh(const Dado& valor){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Chave = valor;
}
    
class Arvore{
    private:
      noh* Raiz;
      noh* BuscaAux(Dado valor);
      noh* MinimoAux(noh* aux);
      void Transplanta(noh* antigo,noh* novo);
      void PercorreEmOrdem(noh* aux);
      void PercorreEmPreOrdem(noh* aux); 
      void Destrucao(noh* aux);
      void PreOrdem1(int& AlturaNoh, noh* aux, int nivel);
    public:
      Arvore();
      ~Arvore();
      void Inserir(Dado valor);
      void Remover(Dado valor);
      void PreOrdem();
      void PreOrdemAux();
      void Ordem();
      void AlturaArvore();
};

void Arvore::PreOrdem1(int &AlturaNoh,noh* aux, int nivel){
    if(aux != NULL){
        PreOrdem1(AlturaNoh,aux->FilhoEsquerdo, nivel+1);
        PreOrdem1(AlturaNoh,aux->FilhoDireito, nivel+1);
    }
    if (AlturaNoh<nivel){
        AlturaNoh=nivel-1;
    }
}

void Arvore::PreOrdemAux(){
    int AlturaNoh = 0;
    PreOrdem1(AlturaNoh,Raiz, 0);
    cout << AlturaNoh << endl;
}

Arvore::Arvore(){
    Raiz = NULL;
}

Arvore::~Arvore(){
    Destrucao(Raiz);
}

noh* Arvore::BuscaAux(Dado valor){
    noh* atual = Raiz;
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

noh* Arvore::MinimoAux(noh* aux){
    while(aux->FilhoEsquerdo != NULL){
        aux = aux->FilhoEsquerdo;
    }
    return aux;
}

void Arvore::Transplanta(noh* antigo,noh* novo){
    if(Raiz == antigo){
        Raiz = novo;
    }else if(antigo == antigo->Pai->FilhoEsquerdo){
        antigo->Pai->FilhoEsquerdo = novo;
    }else{
        antigo->Pai->FilhoDireito = novo;
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}

void Arvore::PercorreEmOrdem(noh* aux){
    if(aux != NULL){
        PercorreEmOrdem(aux->FilhoEsquerdo);
        cout << aux->Chave <<" ";
        PercorreEmOrdem(aux->FilhoDireito);
    }
}

void Arvore::PercorreEmPreOrdem(noh* aux){
    if(aux != NULL){
        cout << aux->Chave <<" ";
        PercorreEmPreOrdem(aux->FilhoEsquerdo);
        PercorreEmPreOrdem(aux->FilhoDireito);
    }
}

void Arvore::Destrucao(noh* aux){
    if(aux != NULL){
        noh* atual = aux;
        PercorreEmPreOrdem(aux->FilhoEsquerdo);
        PercorreEmPreOrdem(aux->FilhoDireito);
        delete atual;
    }
}

void Arvore::Inserir(Dado valor){
    noh* novo = new noh(valor);
    if(Raiz == NULL){
        Raiz = novo;
    }else{
        noh* atual = Raiz;
        noh* anterior = NULL;
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

void Arvore::Remover(Dado valor){
    noh* remover = BuscaAux(valor);
    if(remover == NULL){
        cout << "ERRO" << endl;
    }else{
        if(remover->FilhoEsquerdo == NULL){
            Transplanta(remover,remover->FilhoDireito);
        }else if(remover->FilhoDireito == NULL){
            Transplanta(remover,remover->FilhoEsquerdo);
        }else{
            noh* sucessor = MinimoAux(remover->FilhoDireito);
            if(sucessor->Pai != remover){
                Transplanta(sucessor,sucessor->FilhoDireito);
                sucessor->FilhoDireito = remover->FilhoDireito;
                sucessor->FilhoDireito->Pai = sucessor;
            }
            Transplanta(remover,sucessor);
            sucessor->FilhoEsquerdo = remover->FilhoEsquerdo;
            sucessor->FilhoEsquerdo->Pai = sucessor;
        }
        remover->FilhoDireito=NULL;
        remover->FilhoEsquerdo=NULL;
        delete remover;
    }
}
    
void Arvore::PreOrdem(){
    PercorreEmPreOrdem(Raiz);
}

void Arvore::Ordem(){
    PercorreEmOrdem(Raiz);
}

void Arvore::AlturaArvore(){
    int altura = 0;
    int nivel = 0;
    PreOrdem1(altura,Raiz,nivel);
    cout << altura << endl;
}

int main(){
    Arvore abb;
    Dado chave;
    char operacao;
    do{
        cin >> operacao;
        switch(operacao){
            case 'i':
                cin >> chave;
                abb.Inserir(chave);
                break;
            case 'r':
                cin >> chave;
                abb.Remover(chave);
                break;
            case 'o':
                abb.Ordem();
                cout << endl;
                break;
            case 'p':
                abb.PreOrdem();
                cout << endl;
                break;
            case 'e':
                abb.PreOrdemAux();
                cout << endl;
                break;
            case 'a':
                abb.AlturaArvore();
                cout << endl;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
        }while(operacao != 'f');
        return 0;
}
            
