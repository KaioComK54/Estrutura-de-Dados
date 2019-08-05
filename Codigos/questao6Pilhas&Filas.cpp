
/* Classe fila, um fila (FIFO) implementada usando encadeamento
 * 
 * by Joukim, 2017, Estruturas de Dados
 * adaptada por Valéria, 2018
 */

#include <iostream>

using namespace std;

class noh {
	friend class fila;
	private:
		int dado; // poderia ser outro tipo de variável
		noh* prox;
};

// pilha dinamicamente encadeada
class fila {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
    
	public:
		fila();
		fila(const fila& umaFila);
		~fila();
		void insere(int d) { enfileira(d); }
		void enfileira(int d); // insere no final da fila 
		int desenfileira(); // retorna o primeiro elemento da fila
		int espia(); // espia o primeiro elemento da fila
		bool vazia();
		void imprime();  
		fila operator+(const fila& umaFila) const;
                fila& operator=(const fila& umaFila);
};

fila::fila() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

fila::~fila() { 
    while (primeiro != NULL) {
        desenfileira();
    }
}

void fila::enfileira(int d) {
    // primeiro criamos o novo nó
    noh* temp = new noh;
    temp->dado = d;
    temp->prox = NULL;
    if (ultimo != NULL) {
        ultimo->prox = temp;
    }
    ultimo = temp;
    if (vazia()) {
        primeiro = temp;
    }    
    tamanho++; 
}

int fila::desenfileira() {
    int removido;
    noh* temp;
    removido = primeiro->dado;
    temp = primeiro;
    primeiro = primeiro->prox;
    if (vazia()){
        ultimo = NULL;
    }
    delete temp;
    tamanho--;
    return removido;    
}

int fila::espia(){
    return primeiro->dado;
}
    
bool fila::vazia() {
    return (primeiro == NULL);
}

void fila::imprime(){
    noh* temp = primeiro;
    while (temp != NULL) {
	cout << temp->dado << " ";
        temp = temp->prox;
    }
    cout << endl;
}


fila fila::operator+(const fila& umaFila) const {
    fila fila3;
    noh* aux = primeiro;
    noh* aux2 = umaFila.primeiro;
    int tam = tamanho + umaFila.tamanho;
    int i = 0;
    while(i < tam){
        if(aux == NULL){
            fila3.enfileira(aux2->dado);
            aux2 = aux2->prox;
        }else if(aux2 == NULL){
            fila3.enfileira(aux->dado);
            aux = aux->prox;
        }else if((aux->dado < aux2->dado) or (aux2 == NULL)){
            fila3.enfileira(aux->dado);
            aux = aux->prox;
        }else if((aux->dado > aux2->dado)or(aux == NULL)){
            fila3.enfileira(aux2->dado);
            aux2 = aux2->prox;
        }
        ++i;
    }
    return fila3;

}


fila& fila::operator=(const fila& umaFila){
    while(not vazia()){
        desenfileira();
    }
    noh* aux = umaFila.primeiro;
    while(aux!=NULL){
        enfileira(aux->dado);
        aux = aux->prox;
    }
    return *this;
}


fila::fila(const fila& umaFila) {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    noh* aux = umaFila.primeiro;
    while(aux!=NULL){
        enfileira(aux->dado);
        aux = aux->prox;
    }
}

int main() {
    fila filaA;
    fila filaB;
    string opcao;
    int dado;
    char idFila;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idFila >> dado;
            if (idFila == 'a')
                filaA.enfileira(dado);
            else
                filaB.enfileira(dado);
        }
 	else if (opcao == "a=b") {
            filaA = filaB;
        }
        else if (opcao == "b=a") {
            filaB = filaA;
        }
        else if (opcao == "s") {
            fila filaM = filaA + filaB;
            filaM.imprime();
        }
        else if (opcao == "e") {
            cin >> idFila;
            if (idFila == 'a')
                filaA.imprime();
            else
                filaB.imprime();
        }
    } while (opcao != "t");
    return 0;
}
