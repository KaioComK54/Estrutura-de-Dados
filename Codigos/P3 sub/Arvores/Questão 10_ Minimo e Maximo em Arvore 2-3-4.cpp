// Árvore 2-3-4  
// (Árvore B em memória, com nós com capacidade para 2, 3 ou 4 filhos)
// Estruturas de Dados - 2018/2
// Código by Joukim

#include <iostream>

using namespace std;

// constantes para verificação
const int MAXITENS = 3;
const int MINITENS = 1;
const int MAXFILHOS = 4;


// posição do elemento do meio (o que sobe para página pai em caso de estouro)
const int MEIO = 1; 
const int METADE = 1;
typedef float Dado;

class Noh {
friend class Arvore234;
private:
    bool folha;
    int num; // número de itens armazenadas no nó
    Dado itens[MAXITENS];
    Noh* filhos[MAXFILHOS];
    Noh* pai;
public:
    Noh();
    ~Noh();
};

Noh::Noh() {
    num = 0;
    folha = false;
    for (int i = 0; i < MAXFILHOS; i++) {
        filhos[i] = NULL;
    }
}

Noh::~Noh() {
    for (int i = 0; i < num+1; i++) {
        delete filhos[i];
    }
}

class Arvore234 {
private:
    Noh* raiz;
    void percorreEmOrdemAux(Noh* atual, int nivel);   
public:
    Arvore234() { raiz = NULL; }
    ~Arvore234() { delete raiz; }
    // código não implementado, sua tarefa é implementá-lo!
    void insereFolhaNaoCheio(Noh* umNoh, Dado umItem);
    Noh* divide (Noh* umNoh, Dado &itemPromovido);
    void insereItermediarioNaoCheio(Noh* umNoh, Noh* novo, Dado &itemPromovido);
    Noh* insereAux(Noh* umNoh, Dado umItem, Dado &itemPromovido);
    void insere(Dado umItem);
    // percorrimento (impressão)
    void percorreEmOrdem();
    Dado minimo();
    Dado maximo();
};

void Arvore234::insereFolhaNaoCheio(Noh* umNoh, Dado umItem){
    int pos = umNoh->num - 1;
    
    while ((pos >= 0) and (umNoh->itens[pos] > umItem)){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    umNoh->itens[pos+1] = umItem;
    umNoh->num++;
}

Noh* Arvore234::divide(Noh* umNoh, Dado &itemPromovido){
    itemPromovido = umNoh->itens[MEIO];
    Noh* novo = new Noh();
    novo->folha = umNoh->folha;
    novo->itens[0] = umNoh->itens[MEIO+1];
    novo->num = METADE;
    umNoh->num = METADE;
    
    if(not(umNoh->folha)){
        for (int i = 0; i < MEIO+1; i++){
            novo->filhos[i] = umNoh->filhos[MEIO+1+i];
        }
    }
    return novo;
        
}

void Arvore234::insereItermediarioNaoCheio(Noh* umNoh, Noh* novo, Dado &itemPromovido){
    int pos = umNoh->num - 1;
    
    while (pos >= 0 and umNoh->itens[pos] > itemPromovido){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    umNoh->itens[pos+1] = itemPromovido;
    umNoh->filhos[pos+2] = novo;
    umNoh->num++;    
}

void Arvore234::insere(Dado umItem) {
    if (raiz == NULL) {
        raiz = new Noh();
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->num = 1;
    } else {
        Dado itemPromovido = 0;
        Noh* novo = insereAux(raiz,umItem,itemPromovido);
        if (novo != NULL){
            Noh* antiga = raiz;
            raiz = new Noh();
            raiz->itens[0] = itemPromovido;
            raiz->num = 1;
            raiz->filhos[0] = antiga;
            raiz->filhos[1] = novo;
        }
    }
}

Noh* Arvore234::insereAux(Noh* umNoh, Dado umItem, Dado &itemPromovido){
    if (umNoh->folha){
        if (umNoh->num < MAXITENS){
            insereFolhaNaoCheio(umNoh, umItem);
            itemPromovido = 0;
            return NULL;
        } else {
            Noh* novo = divide(umNoh, itemPromovido);
            if (umItem <= umNoh->itens[MEIO]){
                insereFolhaNaoCheio(umNoh,umItem);
            } else {
                insereFolhaNaoCheio(novo, umItem);
            }
            return novo;
        }
    } else {
        int pos = umNoh->num - 1;
        while ((pos >= 0) and (umNoh->itens[pos] > umItem)){
            pos--;
        }
        Noh* aux = insereAux(umNoh->filhos[pos+1], umItem, itemPromovido);
        if (aux != NULL){
            if (umNoh->num < MAXITENS){
                insereItermediarioNaoCheio(umNoh,aux,itemPromovido);
                return NULL;
            } else {
                Dado itemPf = itemPromovido;
                Noh* novo = divide(umNoh, itemPromovido);
                
                if (umItem <= umNoh->itens[MEIO]){
                    insereItermediarioNaoCheio(umNoh, aux, itemPf);
                } else {
                    insereItermediarioNaoCheio(umNoh,aux, itemPf);
                }
                return novo;
            }
        }
        return NULL;
    } 
}
            

void Arvore234::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);        
    cout<< endl;
}

void Arvore234::percorreEmOrdemAux(Noh* umNoh, int nivel) {
    int i;
    for (i = 0; i < umNoh->num; i++) {
        // se nó não é folha, imprima os dados do filho i
        // antes de imprimir o item i
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1); 
        }
        cout << umNoh->itens[i] << '/' << nivel << ' ';
    }
 
    // Imprima os dados do último filho
    if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);   
    }
}

Dado Arvore234::minimo(){
    Noh* atual = raiz;
    while (!(atual->folha)){
        atual = atual->filhos[0];
    }
    return atual->itens[0];
}

Dado Arvore234::maximo(){
    Noh* atual = raiz;
    if (raiz->folha){
        return atual->itens[atual->num-1];
    }
    while (!(atual->folha)){
        atual = atual->filhos[atual->num-1];
    }
    return atual->itens[atual->num];
}

// =========================== Programa ================================
int main() {
    Arvore234* B = new Arvore234;
    
    char opcao;
    float valor;
    
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i':
                cin >> valor;
                B->insere(valor);
                break;
            case 'l': 
                cout << B->minimo() << endl;
                break;
            case 'h':
                cout << B->maximo() << endl;
                break;
            case 'e':
                B->percorreEmOrdem();
            break;
        }
    } while (opcao != 'q');
    
    
    
    delete B;    
    
    return 0;
}
