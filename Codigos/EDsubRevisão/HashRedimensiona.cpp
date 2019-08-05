#include <iostream>

using namespace std;

const int Valor = 13;

int FuncaoHash(string Texto,int Cap){
    int h = 0;
    for(unsigned i = 0;i < Texto.size();i++){
        h = (h*Valor + Texto[i])% Cap;
    }
    return h;
}
        
        
class Noh{
    friend class Hash;
    private:
        Noh* Proximo;
        int Valor;
        string Chave;
    public:
        Noh(int valor,string chave);
};

Noh::Noh(int valor,string chave){
    Proximo = NULL;
    Valor = valor;
    Chave = chave;
}

class Hash{
    private:
        Noh** Elementos;
        int Capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Inserir(string texto,int valor);
        void Remover(string texto);
        int Recuperar(string texti);
        void Redimensiona();
        void Escrever();
};

Hash::Hash(int cap){
    Capacidade = cap;
    Elementos = new Noh*[cap];
    for(int i = 0;i < cap;i++){
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

void Hash::Inserir(string texto,int valor){
    if(Recuperar(texto) == 0){
        int h = FuncaoHash(texto,Capacidade);
        if(Elementos[h] == NULL){
            Noh* aux = new Noh(valor,texto);
            Elementos[h] = aux;
        }else{
            Noh* novo = new Noh(valor,texto);
            Noh* atual = Elementos[h];
            while(atual->Proximo != NULL){
                atual = atual->Proximo;
            }
            atual->Proximo = novo;
        }
    }else{
        cerr << "Chave e Valor ja existem" << endl;
    }
}

int Hash::Recuperar(string texto){
    int h = FuncaoHash(texto,Capacidade);
    if(Elementos[h] == NULL or (Elementos[h]->Chave != texto and Elementos[h]->Proximo == NULL)){
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
    if(Recuperar(texto) == 0){
        cerr << "Chave e Valor nao existem" << endl;
    }else{
        int h = FuncaoHash(texto,Capacidade);
        if(Elementos[h]->Chave == texto and Elementos[h]->Proximo == NULL){
            Noh* aux = Elementos[h];
            Elementos[h] = Elementos[h]->Proximo;
            delete aux;
        }else if(Elementos[h]->Chave == texto and Elementos[h]->Proximo != NULL){
            Noh* aux = Elementos[h];
            Elementos[h] = Elementos[h]->Proximo;
            delete aux;
        }else{
            Noh* aux = Elementos[h];
            Noh* anterior = NULL;
            while(aux->Chave != texto){
                anterior = aux;
                aux = aux->Proximo;
            }
            if(aux == NULL){
                cerr << "Chave e Valor nao existem" << endl;
            }else{
                anterior->Proximo = aux->Proximo;
                delete aux;
            }
        }
    }
}

void Hash::Escrever(){
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] == NULL){
            cout << i <<" : "<<"[]->"<< endl;
        }else{
            Noh* aux = Elementos[i];
            cout << i <<" : ";
            while(aux != NULL){
                cout << "[" << aux->Chave << "/" << aux->Valor << "]->" <<" ";
                aux = aux->Proximo;
            }
            cout << endl;
        }
    }
}

void Hash::Redimensiona(){
    Hash* Aux = new Hash(Capacidade+10);
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] != NULL){
            Noh* aux = Elementos[i];
            while(aux != NULL){
                Aux->Inserir(aux->Chave,aux->Valor);
                aux = aux->Proximo;
            }
        }
    }
    for(int i = 0;i < Capacidade;i++){
        Noh* aux = Elementos[i];
        while(aux != NULL){
            Noh* anterior = aux;
            aux = aux->Proximo;
            delete anterior;
        }
    }
    delete[] Elementos;
    Capacidade += 10;
    Elementos = new Noh*[Capacidade];
    for(int i = 0;i < Capacidade;i++){
        Elementos[i] = NULL;
    }
    for(int i = 0;i < Capacidade;i++){
        if(Aux->Elementos[i] != NULL){
            Noh* aux = Aux->Elementos[i];
            while(aux != NULL){
                Inserir(aux->Chave,aux->Valor);
                aux = aux->Proximo;
            }
        }
    }
    delete Aux;
}

int main(){
    Hash Teste(20);
    string chave;
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> chave;
                cin >> valor;
                Teste.Inserir(chave,valor);
                break;
            case 'r':
                cin >> chave;
                Teste.Remover(chave);
                break;
            case 'v':
                cin >> chave;
                if(Teste.Recuperar(chave) == 0){
                    cerr << "Chave e Valor nao existem" << endl;
                }else{
                    cout << Teste.Recuperar(chave) << endl;
                }
                break;
            case 'e':
                Teste.Escrever();
                cout << endl;
                break;
            case 'd':
                Teste.Redimensiona();
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}

                

            
            
