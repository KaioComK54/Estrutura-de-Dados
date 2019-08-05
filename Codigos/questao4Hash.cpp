#include <iostream>
#include <string>

using namespace std;

const int UMPRIMO = 23;

int funcaoHash(string c) {
    int h=static_cast<int>(c.length()%23);
    return h;
}

class noh {
    friend class tabelaHash;
    private:
        string chave;
        string valor;
        noh* proximo = NULL;
    public:
        noh(string c, string v) {
            chave = c;
            valor = v;
        }
};

class tabelaHash {
    private:
        // vetor de ponteiros de nós
        noh** elementos;
        int capacidade;
    public:
        // construtor padrão
        tabelaHash(int cap = 23);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(string c, string v);
        // recupera um valor associado a uma dada chave
        string recupera(string c);
        // altera o valor associado a uma chave
        void procura(string c);
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;
    for (int i = 0; i < cap; i++)
        elementos[i] = NULL;
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = elementos[i];
        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

// Insere um valor v com chave c.
void tabelaHash::insere(string c, string v) {
    int h;
    h=funcaoHash(c);
    if(elementos[h] == NULL){
        elementos[h] = new noh(c, v);
    }
    else{//se recupera() retorna um valor, então ele colidiu
		if(recupera(c) == "NAO ENCONTRADO!"){
			noh* atual = elementos[h];
			while(atual -> proximo != NULL){
				atual = atual -> proximo;
			}
			noh* novo = new noh (c,v);
			atual -> proximo = novo;
		}
	}
}

// recupera um valor associado a uma dada chave
string tabelaHash::recupera(string c) {
    int h;
    h = funcaoHash(c);

    if ((elementos[h] != NULL) and (elementos[h]->chave == c)) {
        return elementos[h]->valor;
    } else {
        noh* atual = elementos[h];

        while ((atual != NULL) and (atual->chave != c)) {
            atual = atual->proximo;
        }

        if ((atual != NULL) and (atual->chave == c)) {
            return atual->valor;
        } else {
            return "NAO ENCONTRADO!";
        }
    }
}

void tabelaHash::procura(string c) {
    if (recupera(c)!="NAO ENCONTRADO!")
    {
        cout << "[" << c << "]" 
        << " => " << recupera(c) << endl;
        }
    else {
        cout << "[" << c << "]" 
        << " => " << "NULL" << endl;}
}


int main( ) {
    tabelaHash th(23);
    int qtdade;
    string c;
    string v;
    // insercao na tabela
    cin >> qtdade;
    for (int i=0; i < qtdade; i++) {
        cin >> c;
        getline(cin, v);
        th.insere(c, v);
    }
    string texto;
    cin >> texto;
    while (texto != "-1")
    {
        th.procura(texto);
        cin >> texto;
    }

    return 0;
}

