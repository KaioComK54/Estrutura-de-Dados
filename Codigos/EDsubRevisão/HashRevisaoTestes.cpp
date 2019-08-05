#include <iostream>

using namespace std;

const int UMVALOR = 31;


int FuncaoHash(string texto,int Cap){
    int h = 0;
    for(unsigned i = 0;i < texto.size();i++){
        h = (h * UMVALOR + texto[i]) % Cap;
    }
    return h;
}

class Noh {
    friend class Hash;
    private:
        Noh* Proximo;
        string Chave;
        int Valor;
    public:
        Noh(string texto,int valor);
};

Noh::Noh(string texto,int valor){
    Proximo = NULL;
    Chave = texto;
    Valor = valor;
}

class Hash {
    private:
        Noh* Vazio;
        Noh** Elementos;
        int Capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Inserir(string texto,int valor);
        int Recuperar(string texto);
        void Remover(string texto);
        void Escrever();
};

Hash::Hash(int cap){
    Vazio = NULL;
    Elementos = new Noh*[cap];
    for(int i = 0;i < cap;i++){
        Elementos[i] = Vazio;
    }
    Capacidade = cap;
}

Hash::~Hash(){
    for(int i = 0;i < Capacidade;i++){
        Noh* aux = Elementos[i];
        while(aux != NULL){
            Noh* anterior = aux;
            aux = aux->Proximo;
            delete anterior;
        }
    }
    delete[] Elementos;
}

void Hash::Inserir(string texto,int valor){
    int h = FuncaoHash(texto,Capacidade);
    if(Recuperar(texto) == 0){
        Noh* novo = new Noh(texto,valor);
        if(Elementos[h] == NULL){
            Elementos[h] = novo;
        }else{
            Noh* atual = Elementos[h];
            while(atual->Proximo != NULL){
                atual = atual->Proximo;
            }
            atual->Proximo = novo;
        }
    }else{
        cerr << "Chave Ja Registrada" << endl;
    }
}
            
int Hash::Recuperar(string texto){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == NULL or(Elementos[h]->Chave != texto and Elementos[h]->Proximo == NULL)){
        return 0;
    }else{
        Noh* atual = Elementos[h];
        while(atual != NULL){
            if(atual->Chave == texto){
                return atual->Valor;
            }else{
                atual = atual->Proximo;
            }
        }
        return 0;
    }
}

void Hash::Remover(string texto){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == Vazio or (Elementos[h]->Chave != texto and Elementos[h]->Proximo == NULL)){
        cerr << "Chave Nao Encontrada" << endl;
    }else{
        if(Elementos[h]->Chave == texto and Elementos[h]->Proximo == NULL){
            Noh* aux = Elementos[h];
            Elementos[h] = Elementos[h]->Proximo;
            delete aux;
        }else{
            Noh* aux = Elementos[h];
            Noh* anterior = NULL;
            while(aux != NULL and aux->Chave != texto){
                anterior = aux;
                aux = aux->Proximo;
            }
            if(aux == NULL){
                cerr << "Chave Nao Encontrada" << endl;
            }else{
                anterior->Proximo = aux->Proximo;
                delete aux;
            }
        }
    }
}

void Hash::Escrever(){
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] == Vazio){
            cout << i <<" "<<":"<<" "<<"["<<"Vazio"<<"]"<<" "<<"->" << endl;
        }else{
            Noh* aux = Elementos[i];
            cout << i <<" "<<":"<<" ";
            while(aux != NULL){
                cout <<"["<<aux->Chave<<"/"<<aux->Valor<<"]"<<"->";
                aux = aux->Proximo;
            }
            cout << endl;
        }
    }
}

int main(){
    Hash teste(20);
    string texto;
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> texto;
                cin >> valor;
                teste.Inserir(texto,valor);
                break;
            case 'r':
                cin >> texto;
                teste.Remover(texto);
                break;
            case 'e':
                teste.Escrever();
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
        }while(opcao != 'f');
    return 0;
}
