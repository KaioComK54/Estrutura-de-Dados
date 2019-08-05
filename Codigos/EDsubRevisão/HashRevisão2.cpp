#include <iostream>

using namespace std;

const int UMPRIMO = 17;

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
        string Chave;
        int Valor;
    public:
        Noh(string texto,int dado);
};

Noh::Noh(string texto,int dado){
    Proximo = NULL;
    Chave = texto;
    Valor = dado;
}

class Hash {
    private:
        Noh** Elementos;
        int Capacidade;
    public:
        Hash(int cap);
        ~Hash();
        void Inserir(string texto,int valor);
        int Recuperar(string texto);
        void Remover(string texto);
        void Escrever();
        void Redimensiona();
};

Hash::Hash(int cap){
    Capacidade = cap;
    Elementos = new Noh*[cap];
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
    if(h < Capacidade){
        if(Elementos[h] == NULL or (Elementos[h]->Chave != texto and Elementos[h]->Proximo == NULL)){
            cerr << "Valor Nao Encontrado" << endl;
        }else{
            if(Elementos[h]->Chave == texto and Elementos[h]->Proximo == NULL){
                Noh* aux = Elementos[h];
                Elementos[h] = Elementos[h]->Proximo;
                delete aux;
            }else{
                Noh* atual = Elementos[h];
                Noh* anterior = NULL;
                while(atual != NULL and atual->Chave != texto){
                    anterior = atual;
                    atual = atual->Proximo;
                }
                if(atual == NULL){
                    cerr << "Valor Nao Encontrado" << endl;
                }else{
                    anterior->Proximo = atual->Proximo;
                    delete atual;
                }
            }
        }
    }
}

void Hash::Escrever(){
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] == NULL){
            cout << i <<" "<<":"<<" "<<"["<<"]" << endl;
        }else{
            Noh* aux = Elementos[i];
            cout << i << " " << ":";
            while(aux != NULL){
            cout << " " << "[" << aux->Chave << "/" << aux->Valor << "]" << " " << "-" << ">" << " ";
            aux = aux->Proximo;
            }
            cout << endl;
        }
    }
}

void Hash::Redimensiona(){
    Hash* HashAux = new Hash(Capacidade+20);
    for(int i = 0;i < Capacidade;i++){
        if(Elementos[i] != NULL){
            Noh* aux = Elementos[i];
            while(aux != NULL){
                HashAux->Inserir(aux->Chave,aux->Valor);
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
    Capacidade += 20;
    Elementos = new Noh*[Capacidade];
    for(int i = 0;i < Capacidade;i++){
        Elementos[i] = NULL;
    }
    for(int i = 0;i < Capacidade;i++){
        if(HashAux->Elementos[i] != NULL){
            Noh* aux = HashAux->Elementos[i];
            while(aux != NULL){
                Inserir(aux->Chave,aux->Valor);
                aux = aux->Proximo;
            }
        }
    }
    delete HashAux;
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
            case 'b':
                cin >> texto;
                if(teste.Recuperar(texto) == 0){
                    cerr << "Valor Nao Encontrado" << endl;
                }else{
                    cout << teste.Recuperar(texto) << endl;
                }
                break;
            case 'e':
                teste.Escrever();
                break;
            case 'd':
                teste.Redimensiona();
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}
