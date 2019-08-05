#include <iostream>
using namespace std;

typedef float Dado;

class noh {
  friend class listadup;
  private:
    const Dado dado;
    noh* proximo;
    noh* anterior;
  public:
    noh(Dado d = 0) : dado(d) {
      proximo = NULL;
      anterior = NULL;
    }
};

// lista dinamicamente encadeada
class listadup {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
  public:
    listadup() {
      // constrói uma lista inicialmente vazia
      tamanho = 0;
      primeiro = NULL;
      ultimo = NULL;
    };
    ~listadup() {
      // destroi a lista
      noh* atual = primeiro;
      while (atual != NULL) {
        noh* aux = atual;
        atual = atual->proximo;
        delete aux;
      }
    };
    void RemoveFinal(){
      noh* anterior = primeiro;
      int i=0;
      while(anterior!=NULL and i<tamanho-2){
            anterior = anterior->proximo;
            ++i;
        }
        ultimo = anterior;
        delete anterior->proximo;
        anterior->proximo = NULL;
        --tamanho;
    };
    inline void insere(Dado dado) {
      // insere por padrão no final da lista
      // TODO - implementar
      noh* aux = new noh(dado);
      if(tamanho==0){
          primeiro = aux;
          ultimo = aux;
          ++tamanho;
      }else if(tamanho>0){
          ultimo->proximo = aux;
          aux->anterior = ultimo;
          ultimo = aux;
          ++tamanho;
      }
    };
    listadup* separa(int n) {
    if(n>=0 and n<tamanho and tamanho>0){
          listadup* lista3 = new listadup();
          if(n > 0){
              noh* aux = primeiro;
              noh* anterior = NULL;
              int i = 0;
              while(i < n){
                  anterior = aux;
                  aux = aux->proximo;
                  ++i;
              }
              while(aux != NULL){
                  lista3->insere(aux->dado);
                  noh* lixo = aux;
                  aux = aux->proximo;
                  delete lixo;
                  --tamanho;
              }
              ultimo = anterior;
              ultimo->proximo = NULL;
              lista3->primeiro->anterior = NULL;
          }else if(n == 0 and primeiro == ultimo){
              noh* aux = primeiro;
              lista3->insere(aux->dado);
              delete aux;
              --tamanho;
              primeiro = NULL;
              ultimo = NULL;
              lista3->primeiro->anterior = NULL;
          }else if(n == 0 and primeiro != ultimo){
              noh* aux = primeiro;
              while(aux != NULL){
                  lista3->insere(aux->dado);
                  noh* aux2 = aux;
                  aux = aux->proximo;
                  delete aux2;
                  --tamanho;
              }
              primeiro->anterior = NULL;
              lista3->primeiro->anterior = NULL;
          }
          if(tamanho == 1){
              primeiro->anterior = NULL;
              primeiro->proximo = NULL;
              ultimo = primeiro;
          }
          return lista3;
      }
      cerr << "erro!" << endl;
      return NULL;
    };
    void imprime() {
      // método básico que *percorre* uma lista, imprimindo seus elementos
      noh* aux = primeiro;
      
      if (aux == NULL) {
        cout << "vazio!";
      } else {
        while (aux != NULL) {
          cout << aux->dado << " ";
          aux = aux->proximo;
        }
      }
      
      cout << " <> ";
      
      // imprime reverso (para mostrar duplo encadeamento)
      aux = ultimo;
      if (aux == NULL) {
        cout << "vazio!";
      } else {
        while (aux != NULL) {
          cout << aux->dado << " ";
          aux = aux->anterior;
        }
      }
      
      cout << endl;
    };
};


// NÃO MODIFICAR
int main() {
  listadup* minhaLista = new listadup();
  
  char opcao;
  float valor;

  do {
    cin >> opcao;

    switch(opcao) {
      case 'I':
        cin >> valor;
        minhaLista->insere(valor);
        break;
      case 'S':
        cin >> valor;
        listadup* outraLista = minhaLista->separa(valor);
        if (outraLista != NULL) {
          outraLista->imprime();
          delete outraLista;
        } 
        break;
    }
  } while (opcao != 'Q');

  minhaLista->imprime();
  
  delete minhaLista;

  return 0;
}

