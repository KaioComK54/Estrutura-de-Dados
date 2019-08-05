#include <iostream>
using namespace std;

typedef unsigned Dado;

class aluno{
  friend class lista;
  private:
    Dado matricula;
    string nome;
    aluno* proximo;
    aluno* anterior;
    public:
        aluno(Dado matricula, string nome);
};
aluno::aluno(Dado matricula, string nome): matricula(matricula), nome(nome){
    proximo=NULL;
    anterior=NULL;
}
class lista {
  private:
    aluno* primeiro;
    aluno* ultimo;
    int tamanho;
  public:
    lista() {
      tamanho = 0;
      primeiro = NULL;
      ultimo = NULL;
    };
    ~lista() {
      aluno* atual = primeiro;
      while (atual != NULL) {
        aluno* aux = atual;
        atual = atual->proximo;
        delete aux;
      }
    };
    inline bool vazia(){
        return (primeiro==NULL) and (ultimo==NULL);
    };
    void insere(Dado matricula,string nome){
        aluno* aux = new aluno(matricula,nome);
        if(vazia()){
            primeiro=aux;
            ultimo=aux;
            ++tamanho;
        }else{
            primeiro->anterior=aux;
            aux->proximo = primeiro;
            primeiro = aux;
            ++tamanho;
        }
    };
    void remover(Dado n){
        if(tamanho == 0){
            cerr << "ERRO" << endl;
        }else if(tamanho > 0){
            Dado valor = 0;
            aluno* aux1 = primeiro;
            while(aux1!=NULL){
                if(aux1->matricula == n){
                    valor = aux1->matricula;
                }
                aux1 = aux1->proximo;
            }
            if(valor == 0){
                cerr << "ERRO" << endl;
            }else{
                aluno* aux = primeiro;
                aluno* antes = NULL;
                aluno* depois = NULL;
                while(aux->matricula != n){
                    aux = aux->proximo;
                }
                if(aux == primeiro){
                    primeiro = aux->proximo;
                    delete aux;
                }else if(aux == ultimo){
                    ultimo = aux->anterior;
                    delete aux;
                }else{
                    antes = aux->anterior;
                    depois = aux->proximo;
                    antes->proximo = depois;
                    depois->anterior = antes;
                    delete aux;
                }
                --tamanho;
            }
        }
        if(tamanho == 0){
            primeiro = NULL;
            ultimo = NULL;
        }else if(tamanho == 1){
            primeiro = ultimo;
            primeiro->anterior = NULL;
            primeiro->proximo = NULL;
        }else{
            ultimo->proximo = NULL;
            primeiro->anterior = NULL;
        }
    };
    void imprimeNormal() {
        aluno* aux = primeiro;
        while (aux != NULL) {
          cout << aux->matricula << " " << aux->nome <<" ";
          aux = aux->proximo;
        }
      cout << endl;
    };
    void imprimeReverso(){
        aluno* aux = ultimo;
        while (aux != NULL) {
            cout << aux->matricula << " " << aux->nome<<" ";
            aux = aux->anterior;
        }
      cout << endl;
    };
};


int main() {
  lista* lista1 = new lista;
  string opcao;
  string nome;
  Dado valor;
  Dado n;
  cin >> opcao;
  while(opcao!="t"){
      if(opcao == "i"){
          cin >> valor;
          cin >> nome;
          lista1->insere(valor,nome);
          cin >> opcao;
      }else if(opcao == "ed"){
          lista1->imprimeNormal();
          cin >> opcao;
      }else if(opcao == "r"){
          cin >> n;
          lista1->remover(n);
          cin >> opcao;
      }else if(opcao == "er"){
          lista1->imprimeReverso();
          cin >> opcao;
      }
  }
  delete lista1;
  return 0;
}
