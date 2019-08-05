#include <iostream>

using namespace std;

class Noh {
    friend class ABB;
    private:
        Noh* Pai;
        Noh* FilhoDireito;
        Noh* FilhoEsquerdo;
        int Valor;
        int QtdValores;
    public:
        Noh(int valor);
        ~Noh();
};


Noh::Noh(int valor){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Valor = valor;
    QtdValores = 1;
}

Noh::~Noh(){
    delete FilhoEsquerdo;
    delete FilhoDireito;
}

class ABB {
    private:
      Noh* Raiz;
      Noh* BuscaAux(int valor);
      Noh* MinimoAux(Noh* aux);
      void Transplanta(Noh* antigo,Noh* novo);
      void PercorreEmOrdem(Noh* aux);
      void PercorreEmPreOrdem(Noh* aux); 
      void Destrucao(Noh* aux);
      void PreOrdem1(int& AlturaNoh, Noh* aux, int nivel);
    public:
      ABB();
      ~ABB();
      void Inserir(int valor);
      void Remover(int valor);
      void PreOrdem();
      void PreOrdemAux();
      void Ordem();
};

void ABB::PreOrdem1(int &AlturaNoh,Noh* aux, int nivel){
    if(aux != NULL){
        PreOrdem1(AlturaNoh,aux->FilhoEsquerdo, nivel+1);
        PreOrdem1(AlturaNoh,aux->FilhoDireito, nivel+1);
    }
    if (AlturaNoh<nivel){
        AlturaNoh=nivel;
    }
}

void ABB::PreOrdemAux(){
    int AlturaNoh = 0;
    PreOrdem1(AlturaNoh,Raiz, 0);
    cout << AlturaNoh << endl;
}

ABB::ABB(){
    Raiz = NULL;
}

ABB::~ABB(){
    delete Raiz;
}

Noh* ABB::BuscaAux(int valor){
    Noh* atual = Raiz;
    while(atual != NULL){
        if(atual->Valor == valor){
            return atual;
        }else if(atual->Valor > valor){
            atual = atual->FilhoEsquerdo;
        }else{
            atual = atual->FilhoEsquerdo;
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
    }else if(antigo == antigo->Pai->FilhoEsquerdo){
        antigo->Pai->FilhoEsquerdo = novo;
    }else{
        antigo->Pai->FilhoDireito = novo;
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}

void ABB::PercorreEmOrdem(Noh* aux){
    if(aux != NULL){
        PercorreEmOrdem(aux->FilhoEsquerdo);
        cout << aux->Valor << "-" << aux->QtdValores <<" ";
        PercorreEmOrdem(aux->FilhoDireito);
    }
}

void ABB::PercorreEmPreOrdem(Noh* aux){
    if(aux != NULL){
        cout << aux->Valor <<"-"<< aux->QtdValores <<" ";
        PercorreEmPreOrdem(aux->FilhoEsquerdo);
        PercorreEmPreOrdem(aux->FilhoDireito);
    }
}

void ABB::Destrucao(Noh* aux){
    if(aux != NULL){
        Noh* atual = aux;
        PercorreEmPreOrdem(aux->FilhoEsquerdo);
        PercorreEmPreOrdem(aux->FilhoDireito);
        delete atual;
    }
}

void ABB::Inserir(int valor){
    Noh* novo = new Noh(valor);
    if(Raiz == NULL){
        Raiz = novo;
    }else{
        Noh* aux = BuscaAux(valor);
        if(aux != NULL){
            aux->QtdValores++;
        }else{
            Noh* atual = Raiz;
            Noh* anterior = NULL;
            while(atual != NULL ){
                anterior = atual;
                if(atual->Valor > valor){
                    atual = atual->FilhoEsquerdo;
                }else{
                    atual = atual->FilhoDireito;
                }
            }
            novo->Pai = anterior;
            if(anterior->Valor > novo->Valor){
                anterior->FilhoEsquerdo = novo;
            }else{
                anterior->FilhoDireito = novo;
            }
        }
    }
}

void ABB::Remover(int valor){
    Noh* remover = BuscaAux(valor);
    if(remover == NULL){
        cout << "ERRO" << endl;
    }else if(remover->QtdValores > 1){
        remover->QtdValores--;
    }else{
        if(remover->FilhoEsquerdo == NULL){
            Transplanta(remover,remover->FilhoDireito);
        }else if(remover->FilhoDireito == NULL){
            Transplanta(remover,remover->FilhoEsquerdo);
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
        remover->FilhoDireito=NULL;
        remover->FilhoEsquerdo=NULL;
        delete remover;
    }
}

void ABB::PreOrdem(){
    PercorreEmPreOrdem(Raiz);
}

void ABB::Ordem(){
    PercorreEmOrdem(Raiz);
}


int main(){
    ABB abb;
    int chave;
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
            }
        }while(operacao != 'f');
        return 0;
}

