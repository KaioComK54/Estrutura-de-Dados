#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

using namespace std;

class Noh {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    private:
        Noh* Pai;
        Noh* FilhoDireito;
        Noh* FilhoEsquerdo;
        int Altura;
        int Chave;
    public:
        Noh(int dado);
        ~Noh();
};

Noh::Noh(int dado){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Altura = 1;
    Chave = dado;
}

Noh::~Noh(){
    delete FilhoEsquerdo;
    delete FilhoDireito;
}

class AVL {
    private:
        Noh* Raiz;
        Noh* MinimoAux(Noh* aux);
        Noh* RotacionarDireita(Noh* aux);
        Noh* RotacionarEsquerda(Noh* aux);
        Noh* RotacionarDireitaEsquerda(Noh* aux);
        Noh* RotacionarEsquerdaDireita(Noh* aux);
        Noh* InserirAux(Noh* aux,int chave);    
        Noh* ArrumarBalanceamento(Noh* aux);
        int RetornaAltura(Noh* aux);
        void AtualizarAltura(Noh* aux);
        int FatorBalanceamento(Noh* aux);
    public:
        AVL();
        ~AVL();
        void Inserir(int valor);
        void EscreverNivelANivel(std::ostream& saida);
};

AVL::AVL(){
    Raiz = NULL;
}

AVL::~AVL(){
    delete Raiz;
}

Noh* AVL::MinimoAux(Noh* aux){
    while(aux->FilhoEsquerdo != NULL){
        aux = aux->FilhoEsquerdo;
    }
    return aux;
}

Noh* AVL::RotacionarDireita(Noh* aux){
    Noh* aux2 = aux->FilhoEsquerdo;
    aux->FilhoEsquerdo = aux2->FilhoDireito;
    if(aux2->FilhoDireito != NULL){
        aux2->FilhoDireito->Pai = aux;
    }
    aux2->Pai = aux->Pai;
    if(aux == Raiz){
        Raiz = aux;
    }else if(aux->Pai->FilhoDireito == aux){
        aux->Pai->FilhoDireito = aux2;
    }else{
        aux->Pai->FilhoEsquerdo = aux2;
    }
    aux2->FilhoDireito = aux;
    aux->Pai = aux2;
    AtualizarAltura(aux);
    AtualizarAltura(aux2);
    return aux2;
}

Noh* AVL::RotacionarEsquerda(Noh* aux){
    Noh* aux2 = aux->FilhoDireito;
    aux->FilhoDireito = aux2->FilhoEsquerdo;
    if(aux2->FilhoEsquerdo != NULL){
        aux2->FilhoEsquerdo->Pai = aux;
    }
    aux2->Pai = aux->Pai;
    if(aux == Raiz){
        Raiz = aux2;
    }else if(aux == aux->Pai->FilhoDireito){
        aux->Pai->FilhoDireito = aux2;
    }else{
        aux->Pai->FilhoEsquerdo = aux2;
    }
    aux2->FilhoEsquerdo = aux;
    aux->Pai = aux2;
    AtualizarAltura(aux);
    AtualizarAltura(aux2);
    return aux2;
}

Noh* AVL::RotacionarDireitaEsquerda(Noh* aux){
    aux->FilhoDireito = RotacionarDireita(aux->FilhoDireito);
    return RotacionarEsquerda(aux);
}

Noh* AVL::RotacionarEsquerdaDireita(Noh* aux){
    aux->FilhoEsquerdo = RotacionarEsquerda(aux->FilhoEsquerdo);
    return RotacionarDireita(aux);
}

Noh* AVL::InserirAux(Noh* aux,int chave){
    if(aux == NULL){
        Noh* novo = new Noh(chave);
        return novo;
    }else{
        if(aux->Chave > chave){
            aux->FilhoEsquerdo = InserirAux(aux->FilhoEsquerdo,chave);
            aux->FilhoEsquerdo->Pai = aux;
        }else{
            aux->FilhoDireito = InserirAux(aux->FilhoDireito,chave);
            aux->FilhoDireito->Pai = aux;
        }
    }
    return ArrumarBalanceamento(aux);
}

int AVL::RetornaAltura(Noh* aux){
    if(aux == NULL){
        return 0;
    }else{
        return aux->Altura;
    }
}

Noh* AVL::ArrumarBalanceamento(Noh* aux){
    AtualizarAltura(aux);
    int FatorBal = FatorBalanceamento(aux);
    if(FatorBal >= -1 and FatorBal <= 1){
        return aux;
    } 
    if(FatorBal > 1 and FatorBalanceamento(aux->FilhoEsquerdo) >= 0){
        return RotacionarDireita(aux);
    }
    if(FatorBal > 1 and FatorBalanceamento(aux->FilhoEsquerdo) < 0){
        aux->FilhoEsquerdo = RotacionarEsquerda(aux->FilhoEsquerdo);
        return RotacionarDireita(aux);
    }
    if(FatorBal < -1 and FatorBalanceamento(aux->FilhoDireito) <= 0){
        return RotacionarEsquerda(aux);
    }
    if(FatorBal < -1 and FatorBalanceamento(aux->FilhoDireito) > 0){
        aux->FilhoDireito = RotacionarDireita(aux->FilhoDireito);
        return RotacionarEsquerda(aux);
    }
    return NULL;
}

int AVL::FatorBalanceamento(Noh* aux){
    int AltArvEsq = RetornaAltura(aux->FilhoEsquerdo);
    int AltArvDir = RetornaAltura(aux->FilhoDireito);
    int FatorBal = AltArvEsq - AltArvDir;
    return FatorBal;
}

void AVL::AtualizarAltura(Noh* aux){
    int AltArvEsq = RetornaAltura(aux->FilhoEsquerdo);
    int AltArvDir = RetornaAltura(aux->FilhoDireito);
    aux->Altura = 1 + max(AltArvEsq,AltArvDir);
}

std::ostream& operator<<(std::ostream& saida, Noh* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->Altura << ':' << ptNoh->Chave <<']';
    return saida;
}

void AVL::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh* fimDeNivel = new Noh(int()); // nÃ³ especial para marcar fim de um nÃ­vel
    filhos.push(Raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            //saida << "\n";
            cout << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            //saida << ptNoh << ' ';
            cout << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->FilhoEsquerdo);
                filhos.push(ptNoh->FilhoDireito);
            }
        }
    }
    delete fimDeNivel;
}
        
int main(){
    AVL minhaArvore;
    char opcao;
    int chave;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave;
                minhaArvore.Inserir(chave);
                break;
            case 'e': // Escrever nÃ³s nÃ­vel a nÃ­vel
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                    break;
            default:
                cerr << "Opcao Invalida" << endl;
        }
    } while (opcao != 'f');
    return 0;
}

