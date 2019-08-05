#include <iostream>

using namespace std;

void FuncaoHash(int chave,int Capacidade,int &Posicao){
    Posicao = chave%Capacidade;
}
    
class Noh{
    friend class Hash;
    private:
        Noh* Proximo;
        int Chave;
    public:
        Noh(int dado);
};

Noh::Noh(int dado){
    Proximo = NULL;
    Chave = dado;
}

class Hash{
    private:
        Noh** Elementos;
        int Capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Insere(int chave);
        void Remove(int chave);
        int Recupera(int chave);
        void Escreve();
        void Redimensiona();
};

Hash::Hash(int cap){
    Elementos = new Noh*[cap];
    for(int i = 0;i < cap;i++){
        Elementos[i] = NULL;
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

int Hash::Recupera(int chave){
    int Posicao = 0;
    FuncaoHash(chave,Capacidade,Posicao);
    if(Elementos[Posicao] != NULL){
        Noh* aux = Elementos[Posicao];
        while(aux != NULL){
            if(aux->Chave == chave){
                return chave;
            }else{
                aux = aux->Proximo;
            }
        }
        return 0;
    }else{
        return 0;
    }
}

void Hash::Insere(int chave){
    if(Recupera(chave) == 0){
        int Posicao = 0;
        FuncaoHash(chave,Capacidade,Posicao);
        Noh* novo = new Noh(chave);
        if(Elementos[Posicao] == NULL){
            Elementos[Posicao] = novo;
        }else{
            Noh* aux = Elementos[Posicao];
            while(aux->Proximo != NULL){
                aux = aux->Proximo;
            }
            aux->Proximo = novo;
        }
    }else{
        cerr << "Chave Ja Registrada" << endl;
    }
}

void Hash::Remove(int chave){
    if(Recupera(chave) != 0){
        int Posicao = 0;
        FuncaoHash(chave,Capacidade,Posicao);
        if(Elementos[Posicao]->Proximo == NULL){
            Noh* aux = Elementos[Posicao];
            Elementos[Posicao] = Elementos[Posicao]->Proximo;
            delete aux;
        }else{
            Noh* anterior = NULL;
            Noh* aux = Elementos[Posicao];
            while(aux->Chave != chave){
                anterior = aux;
                aux = aux->Proximo;
            }
            anterior->Proximo = aux->Proximo;
            delete aux;
        }
    }else{
        cerr << "Chave Nao Registrada" << endl;
    }
}

void Hash::Escreve(){    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] == NULL){
            cout << i <<" "<<":"<<" "<<"["<<"]" << endl;
        }else{
            Noh* aux = Elementos[i];
            cout << i << " " << ":";
            while(aux != NULL){
            cout << " " << "[" << aux->Chave << "]" << " " << "-" << ">" << " ";
            aux = aux->Proximo;
            }
            cout << endl;
        }
    }
}

void Hash::Redimensiona(){
    Hash* aux = new Hash(Capacidade+10);
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] != NULL){
            Noh* atual = Elementos[i];
            while(atual != NULL){
                aux->Insere(atual->Chave);
                atual = atual->Proximo;
            }
        }
    }
    for(int i = 0;i < Capacidade;i++){
        Noh* atual = Elementos[i];
        while(atual != NULL){
            Noh* anterior = atual;
            atual = atual->Proximo;
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
        if(aux->Elementos[i] != NULL){
            Noh* atual = aux->Elementos[i];
            while(atual != NULL){
                Insere(atual->Chave);
                atual = atual->Proximo;
            }
        }
    }
    delete aux;
} 

int main(){
    Hash Teste(20);
    int dado;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> dado;
                Teste.Insere(dado);
                break;
            case 'r':
                cin >> dado;
                Teste.Remove(dado);
                break;
            case 'e':
                Teste.Escreve();
                break;
            case 'd':
                Teste.Redimensiona();
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}

