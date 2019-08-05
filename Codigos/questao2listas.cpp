#include <iostream>

using namespace std;

typedef string Texto;

class noh {
    friend class lista;
    private:
        const Texto palavra;
        noh* proximo;
    public:
        noh(Texto p);
};

noh::noh(Texto p) : palavra(p) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        lista(const lista& umaLista);
        lista& operator=(const lista& umaLista);
        lista operator+(const lista& umaLista) const;
        ~lista();
        void insereNoInicio(Texto palavra);
        void imprime() const;
        void insereNoFinal(Texto palavra);
        void LimparLista();
};

// constrÃ³i uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

void lista::insereNoFinal(Texto palavra){
    noh* novoNoh = new noh(palavra);
    if(tamanho == 0){
        primeiro = novoNoh;
        ultimo = novoNoh;
    }else{
        ultimo->proximo = novoNoh;
        ultimo = novoNoh;
    }
    ++tamanho;
}

// insere no inicio da lista
void lista::insereNoInicio(Texto palavra) {
    noh* novo = new noh(palavra);
    novo->proximo = primeiro;
    primeiro = novo;
    if (tamanho == 0)
        ultimo = novo;
    ++tamanho;
}

// mÃ©todo bÃ¡sico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() const {
    noh* iter = primeiro;
    while (iter != NULL) {
        cout << iter->palavra << " ";
        iter = iter->proximo;
    }
    cout << endl;
}

// construtor de cÃ³pia
lista::lista(const lista& umaLista) {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    noh* aux = umaLista.primeiro;
    while(aux!=NULL){
        insereNoFinal(aux->palavra);
        aux = aux->proximo;
    }
}

void lista::LimparLista(){
    noh* anterior;
    noh* atual = primeiro;
    while (atual!=NULL){
        anterior = atual;
        atual = atual->proximo;
        delete anterior;
    }  
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}
// sobrecarga do operador de atribuiÃ§Ã£o - retorna a prÃ³pria lista
lista& lista::operator=(const lista& umaLista) {
    LimparLista();
    // IMPLEMENTAR
    noh* aux = umaLista.primeiro;
    while(aux!=NULL){
        insereNoFinal(aux->palavra);
        aux = aux->proximo;
    }
    return *this;
}

// concatenacao de listas
lista lista::operator+(const lista& umaLista) const {
    // IMPLEMENTAR
    lista lista3;
    noh* aux = primeiro;
    while(aux!=NULL){
        lista3.insereNoFinal(aux->palavra);
        aux = aux->proximo;
    }
    aux = umaLista.primeiro;
    while(aux!=NULL){
        lista3.insereNoFinal(aux->palavra);
        aux = aux->proximo;
    }
    return lista3;
}


int main() { // NÃƒO MODIFIQUE!
    lista listaA;
    lista listaB;
    string opcao;
    string palavra;
    char idLista;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idLista >> palavra;
            if (idLista == 'a')
                listaA.insereNoInicio(palavra);
            else
                listaB.insereNoInicio(palavra);
        }
        else if (opcao == "a=b") {
            listaA = listaB;
        }
        else if (opcao == "b=a") {
            listaB = listaA;
        }
        else if (opcao == "s") {
            lista soma = listaA + listaB;
            soma.imprime();
        }
        else if (opcao == "e") {
            // escreve _uma copia_ da lista indicada
            cin >> idLista;
            lista* ptLista = (idLista == 'a') ? &listaA : &listaB;
            lista copiaDaLista(*ptLista);
            copiaDaLista.imprime();
        }
    } while (opcao != "t");
    return 0;
}
