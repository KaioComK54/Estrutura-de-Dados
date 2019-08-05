#include <iostream>

using namespace std;
typedef int dado;

class Node{
    public:
        dado valor;
        Node* proximo;
        Node();
};

Node::Node(){
    valor = 0;
    proximo = NULL;
}

class Lista{
    private:
        Node* primeiro;
        Node* ultimo;
        int tamanho;
        inline bool vazia();
    public:
        Lista();
        void inserirNoFim(dado novoDado);
        void inserirNoInicio(dado novoDado);
        void inserir(dado NovoDado,dado posicao);
        void print();
        //~ ~Lista();
};

inline bool Lista::vazia(){
    return (primeiro == NULL) and (ultimo == NULL);
}

void Lista::print(){
    Node* aux = primeiro;
    cout << "Lista:";
    while (aux!=NULL){
        cout << " " << aux->valor; 
        aux = aux->proximo;
    }
    cout << "\nFim" << endl;
}

void Lista::inserirNoFim(dado novoDado){
    Node* novo = new Node();
    novo->valor = novoDado;
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
        ++tamanho;
    }
    else{
        ultimo->proximo = novo;
        ultimo = novo;
        ++tamanho;
    }
}

void Lista::inserirNoInicio(dado novoDado){
    Node* novoNode= new Node();
    novoNode->valor= novoDado;
    if(vazia()){
        primeiro = novoNode;
        ultimo = novoNode;
        ++tamanho;
    }else{
        novoNode->proximo = primeiro;
        primeiro = novoNode;
        ++tamanho;
    }
}

void Lista::inserir(dado novoDado,dado posicao){
    if(posicao<=tamanho){
        Node* aux= primeiro;
        dado cont=1;
        while(aux!= NULL and cont<posicao){
            aux= aux->proximo;
            ++cont;
        }
        Node* Novo = new Node();
        Novo->valor= novoDado;
        Novo->proximo = aux;
        aux = Novo;
    }
}

        

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
}

int main(){
    Lista* list = new Lista;
    dado aux;
    for (int i = 0; i < 5; i++){
        cin >> aux;
        list->inserirNoFim(aux);
    }
    dado posicao;
    dado valor;
    cin >> valor;
    cin >> posicao;
    list->inserir(valor,posicao);
    list->print();
    return 0;
}
 
    
