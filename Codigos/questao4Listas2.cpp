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
        void remove(noh* node);
};

void lista::remove(noh* node){
    if (tamanho == 1){
        primeiro = NULL;
        ultimo = NULL;
    }else{
        if (node == primeiro){
            primeiro = primeiro->proximo;
        }
        if (node == ultimo){
            ultimo = ultimo->anterior;
        }
        node->proximo->anterior=node->anterior;
        node->anterior->proximo=node->proximo;

    }
    tamanho--;
    node->anterior = NULL;
    node->proximo = NULL;
    delete node;
}

lista::lista(){
    tamanho = 0;
    ultimo = NULL;
    primeiro = NULL;
}

lista::~lista(){
    while(tamanho > 0){
        remove(primeiro);
    }
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
            remove(aux);
        }else if(aux == ultimo){
            remove(aux);
        }
        valor = primeiro->valor;
    }
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
    cout << lista1->sobrevivente(pos) << endl;
    delete lista1;
    return 0;
}
