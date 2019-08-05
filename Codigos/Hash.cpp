#include <iostream>

using namespace std;

const int UMPRIMO = 39;

int FuncaoHash(string texto,int cap){
    int h = 0;
    for(unsigned i = 0;i < texto.size();i++){
        h = (UMPRIMO * h + texto[i]) % cap;
    }
    return h;
}

class Noh {
    friend class Hash;
    private:
        Noh* Proximo;
        string chave;
        string valor;
    public:
        Noh(string texto,string Valor);
};


Noh::Noh(string texto,string Valor){
    Proximo = NULL;
    chave = texto;
    valor = Valor;
}

class Hash {
    private:
        Noh** Elementos;
        int Capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Inserir(string texto,string valor);
        string Recuperar(string texto);
        void Remover(string texto);
        void Escrever();
};

Hash::Hash(int cap){
    Capacidade = cap;
    Elementos = new Noh*[Capacidade];
    for(int i = 0;i < Capacidade;i++){
        Elementos[i] = NULL;
    }
}

Hash::~Hash(){
    for(int i = 0;i < Capacidade;i++){
        Noh* atual = Elementos[i];
        while(atual != NULL){
            Noh* anterior = atual;
            atual = atual->Proximo;
            delete anterior;
        }
    }
    delete[] Elementos;
}

void Hash::Inserir(string texto,string valor){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == NULL){
        Elementos[h] = new Noh(texto,valor);
    }else{
        if(Recuperar(texto) != "NAO ENCONTRADO"){
            cerr << "CHAVE JA EXISTE" << endl;
        }else{
            Noh* aux = Elementos[h];
            Noh* anterior = NULL;
            while(aux != NULL and aux->chave != texto){
                anterior = aux;
                aux = aux->Proximo;
            }
            Noh* novo = new Noh(texto,valor);
            anterior->Proximo = novo;
        }
    }
}

string Hash::Recuperar(string texto){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == NULL){
        return "NAO ENCONTRADO";
    }else{
        if(Elementos[h] != NULL and Elementos[h]->chave == texto){
            return Elementos[h]->valor;
        }else{
            Noh* atual = Elementos[h];
            while(atual != NULL and atual->chave != texto){
                atual = atual->Proximo;
            }
            if(atual == NULL){
                return "NAO ENCONTRADO";
            }else{
                return Elementos[h]->valor;
            }
        }
    }
}

void Hash::Escrever(){
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] == NULL){
            cout << i << ":" <<" "<< "[" << "]" << endl;
        }else{
            Noh* aux = Elementos[i];
            string cont;
            cout << i << ":";
            while(aux != NULL){
                cont = cont + aux->valor;
                cout <<" "<< "[" << aux->chave << ":" << aux->valor << "]" <<"-" << ">";
                aux = aux->Proximo;
            }
            cout << cont;
            cout << endl;
        }
    }
}

void Hash::Remover(string texto){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == NULL){
        cerr << "NAO ENCONTRADO" << endl;
    }else{
        if(Elementos[h]->chave == texto and Elementos[h]->Proximo == NULL){
            Noh* aux = Elementos[h];
            Elementos[h] = Elementos[h]->Proximo;
            delete aux;
        }else{
            Noh* atual = Elementos[h];
            Noh* anterior = NULL;
            while(atual != NULL and atual->chave != texto){
                anterior = atual;
                atual = atual->Proximo;
            }
            if(atual == NULL){
                cerr << "NAO ENCONTRADO" << endl;
            }else if(atual->chave == texto){
                anterior->Proximo = atual->Proximo;
                delete atual;
            }
        }
    }
}
            

int main(){
    Hash teste(20);
    char opcao;
    string Chave;
    string Valor;
        do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> Chave;
                cin >> Valor;
                teste.Inserir(Chave,Valor);
                break;
            case 'b':
                cin >> Chave;
                cout << teste.Recuperar(Chave);
                break;
            case 'e':
                teste.Escrever();
                break;
            case 'r':
                cin >> Chave;
                teste.Remover(Chave);
                break;
            }
        }while(opcao != 'f');
    return 0;
}
