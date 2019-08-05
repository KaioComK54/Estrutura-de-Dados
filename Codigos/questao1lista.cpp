#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(Dado dado);
        void insere(Dado dado, int pos);
        void remove(int posicao);
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
};

// constrói uma lista inicialmente vazia
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

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    noh* novoNoh = new noh(dado);
    if(vazia()){
        primeiro = novoNoh;
        ultimo = novoNoh;
    }else{
        ultimo->proximo = novoNoh;
        ultimo = novoNoh;
    }
    ++tamanho;
}

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int posicao) {
    noh* aux = new noh(dado);
    if(vazia()){
        primeiro = aux;
        ultimo = aux;
        ++tamanho;
    }else if(posicao<0 or posicao>tamanho){
        cerr << "Posicao Invalida" << endl;
    }else if(posicao>=0 and posicao<=tamanho){
        if(posicao == 0){
            aux->proximo= primeiro;
            primeiro=aux;
            ++tamanho;
        }else if(posicao == tamanho-1){
            ultimo->proximo = aux;
            ultimo = aux;
            ++tamanho;
        }else{
            noh* anterior = NULL;
            noh* atual = primeiro;
            for(int i=0;i<posicao;++i){
                anterior = atual;
                atual = atual->proximo;
            }
            anterior->proximo = aux;
            aux->proximo = atual;
            ++tamanho;
        }
    }
}



// remove o item da posição passada por parâmetro
// Atenção - o código deve tratar de posição inválidas
void lista::remove(int posicao) {
    if(vazia() or posicao < 0 or posicao >= tamanho){
        cerr << "Posicao Invalida" << endl;
    }else if(posicao>=0 and posicao<tamanho){
        if(posicao == 0){
            noh* aux = primeiro;
            primeiro = aux->proximo;
            delete aux;
        }else if(posicao == tamanho-1){
            noh* anterior = primeiro;
            int i=0;
            while(anterior!=NULL and i<tamanho-2){
                anterior = anterior->proximo;
                ++i;
            }
            ultimo = anterior;
            delete anterior->proximo;
            anterior->proximo = NULL;
        }else{
            noh* aux = primeiro;
            for(int i=0;i<posicao+1;++i){
                aux = aux->proximo;
            }
            noh* anterior = NULL;
            noh* atual = primeiro;
            for(int i=0;i<posicao;++i){
                anterior = atual;
                atual = atual->proximo;
            }
            anterior->proximo = aux;
            delete atual;
        }
        --tamanho;
    }
}
    


// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor) {
	noh* aux = primeiro;
	int cont=0;
	while(aux!= NULL){
		if(aux->dado == valor){
            return cont;
        }else{
            aux=aux->proximo;
        }
    ++cont;
    }
    return -1;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (tamanho == 0);
}

int main() { // NÃO MODIFIQUE!
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insere(valor);
                break;
            case 'W':
                cin >> valor;
                cin >> pos;
                minhaLista.insere(valor, pos);
                break;
            case 'P':
                cin >> valor;
                cout << minhaLista.procura(valor) << endl;
                break;
            case 'R':
                cin >> pos;
                minhaLista.remove(pos);
                break;
            case 'V':
                cout << minhaLista.vazia() << endl;
                break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}
