#include <iostream>

using namespace std;

typedef int Dado;

class noh{
    friend class lista;
    private:
        Dado valor;
        noh* anterior;
        noh* proximo;
    public:
        noh(Dado valor);
};

noh::noh(Dado valor):valor(valor){
    anterior = NULL;
    proximo = NULL;
}

class lista{
    private:
        noh* primeiro;
        noh* ultimo;
        Dado tamanho;
    public:
        lista();
        ~lista();
        void InsereFim(Dado valor);
        void Limpar();
        bool Vazia();
        void imprime();
        Dado sobrevivente(Dado pos);
};

lista::lista(){
    tamanho = 0;
    ultimo = NULL;
    primeiro = NULL;
}

lista::~lista(){
    Limpar();
}

void lista::InsereFim(Dado valor){
      noh* aux = new noh(valor);
      if(Vazia()){
          primeiro = aux;
          ultimo = aux;
          ++tamanho;
      }else{
          ultimo->proximo = aux;
          aux->anterior = ultimo;
          ultimo = aux;
          ultimo->proximo = primeiro;
          primeiro->anterior = ultimo;
          ++tamanho;
      }
}
    
void lista::Limpar(){
    noh* aux = primeiro;
    while(aux != NULL){
        noh* antes = aux;
        aux = aux->proximo;
        delete antes;
        --tamanho;
    }
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

bool lista::Vazia(){
    return (tamanho == 0);
}

void lista::imprime(){
    noh* aux = primeiro;
    Dado i = 0;
    while(i<tamanho){
        cout << aux->valor <<" ";
        aux = aux->proximo;
        ++i;
    }
}

Dado lista::sobrevivente(Dado pos){
    Dado valor = 0;
    while(tamanho > 2){
        Dado cont = 0;
        noh* aux = primeiro;
        while(cont != pos){
            aux = aux->proximo;
            cont++;
        }
        primeiro = aux->proximo;
        ultimo = aux->anterior;
        ultimo->proximo = primeiro;
        primeiro->anterior = ultimo;
        --tamanho;
        delete aux;
    }
    if(tamanho == 2){
        Dado cont = 0;
        noh* aux = primeiro;
        while(cont != pos){
            aux = aux->proximo;
            ++cont;
        }
        if(aux == primeiro){
            ultimo->proximo = NULL;
            ultimo->anterior = NULL;
            delete aux;
            --tamanho;
            return ultimo->valor;
        }else if(aux == ultimo){
            primeiro->anterior = NULL;
            primeiro->proximo = NULL;
            delete aux;
            --tamanho;
            return primeiro->valor;
        }
    }
    //return ((pos%2) == 0) ? primeiro : ultimo;
    return valor;
}

int main(){
    Dado n;
    cin >> n;
    Dado pos;
    cin >> pos;
    lista* lista1 = new lista();
    Dado cont = 1;
    while(cont <= n){
        lista1->InsereFim(cont);
        cont++;
    }
    cout << lista1->sobrevivente(pos);
    delete lista1;
    return 0;
}
    
