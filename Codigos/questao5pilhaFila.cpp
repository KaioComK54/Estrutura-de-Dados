#include <iostream>

using namespace std;

typedef string Dado;

class noh{
    friend class deque;
    private:
        Dado texto;
        noh* proximo;
        noh* anterior;
    public:
        noh(Dado comando);
};

noh::noh(Dado comando){
    texto = comando;
    proximo = NULL;
    anterior = NULL;
}

class deque{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        int capacidade;
    public:
        deque(int tam);
        ~deque();
        bool Vazia();
        void inserir(Dado palavra);
        void Undo();
        void imprime();
        void removeInicio();
};

deque::deque(int tam){
    capacidade = tam;
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

deque::~deque(){
    while(not Vazia()){
        noh* aux = ultimo;
        ultimo = ultimo->anterior;
        delete aux;
        --tamanho;
    }
}

bool deque::Vazia(){
    return (tamanho == 0);
}

void deque::inserir(Dado palavra){
    noh* aux = new noh(palavra);
    if(Vazia()){
        primeiro = aux;
        ultimo = aux;
        ++tamanho;
    }else{
        if(tamanho < capacidade){
            ultimo->proximo = aux;
            ultimo = aux;
            ++tamanho;
        }else if(tamanho == capacidade){
            noh* anterior = ultimo;
            ultimo->proximo = aux;
            ultimo = aux;
            ultimo->anterior = anterior;
            Dado texto1 = primeiro->texto;
            removeInicio();
            cout << "esqueci:" <<" "<< texto1 << endl;
        }
    }
            
}

void deque::removeInicio() {
    noh* aux = NULL;
    if(Vazia()) {
        cerr << "ERRO" << endl;
    } else {
        if(tamanho == 1) {
            primeiro = NULL;
            ultimo = NULL;
            tamanho--;
        } else if(tamanho > 1) {
            aux = primeiro;
            primeiro = aux->proximo;
            primeiro->anterior = NULL;
            delete aux;
            tamanho--;
        }
    }
}

void deque::Undo(){
    if(Vazia()){
        cerr << "ERRO" << endl;
    } else {
        if(tamanho == 1) {
            cout <<"desfazer:"<<" "<< ultimo->texto << endl;
            ultimo = NULL;
            primeiro = NULL;
            tamanho--;
        } else if(tamanho > 1) {
            noh* aux = NULL;
            aux = ultimo;
            cout <<"desfazer:"<<" "<< aux->texto << endl;
            ultimo = aux->anterior;
            ultimo->proximo = NULL;
            delete aux;
            tamanho--;
        }
    }
}

void deque::imprime(){
    noh* aux = primeiro;
    while(aux!=NULL){
        cout << aux->texto <<" ";
        aux = aux->proximo;
    }
    cout << endl;
}

int main(){
    int tam;
    cin >> tam;
    deque* lista1 = new deque(tam);
    Dado comando;
    cin.ignore();
    getline(cin,comando);
    while(comando != "sair"){
        if(comando == "undo"){
            lista1->Undo();
        }else{
            lista1->inserir(comando);
        }
        getline(cin,comando);
    }
    return 0;
}
    
    
