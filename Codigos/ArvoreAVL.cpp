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
        Noh(int Alt);
        ~Noh();
};

Noh::~Noh(){
    delete FilhoEsquerdo;
    delete FilhoDireito;
}

Noh::Noh(int Alt){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Chave = Alt;
    Altura = 1;
}

class AVL {
    private:
        Noh* Raiz;
    public:
        AVL();
        ~AVL();
        void AtualizarAltura(Noh* aux);
        int FatorBalanceamento(Noh* aux);
        Noh* ArrumarBalanceamento(Noh* aux);
        Noh* RotacionarDireita(Noh* aux);
        Noh* RotacionarEsquerda(Noh* aux);
        int RetornaAltura(Noh* aux);
        Noh* InserirAux(Noh* aux,int chave);
        Noh* RotacionarDireitaEsquerda(Noh* aux);
        Noh* RotacionarEsquerdaDireita(Noh* aux);
        void Inserir(int chave);
        void EscreverNivelANivel(std::ostream& saida);
};

AVL::AVL(){
    Raiz = NULL;
}

AVL::~AVL(){
    delete Raiz;
}

int AVL::RetornaAltura(Noh* aux){
    if(aux == NULL){
        return 0;
    }else{
        return aux->Altura;
    }
}

void AVL::AtualizarAltura(Noh* aux){
    int AltArvoreEsq = RetornaAltura(aux->FilhoEsquerdo);
    int AltArvoreDir = RetornaAltura(aux->FilhoDireito);
    aux->Altura = 1 + max(AltArvoreEsq,AltArvoreDir);
}

int AVL::FatorBalanceamento(Noh* aux){
    int AltArvoreEsq = RetornaAltura(aux->FilhoEsquerdo);
    int AltArvoreDir = RetornaAltura(aux->FilhoDireito);
    int FatorBal = AltArvoreEsq - AltArvoreDir;
    return FatorBal;
}

Noh* AVL::RotacionarDireita(Noh* aux){
    Noh* aux2 = aux->FilhoEsquerdo;
    aux->FilhoEsquerdo = aux2->FilhoDireito;
    if(aux2->FilhoDireito != NULL){
        aux2->FilhoDireito->Pai = aux;
    }
    aux2->Pai = aux->Pai;
    if(aux == Raiz){
        Raiz = aux2;
    }else if(aux == aux->Pai->FilhoDireito){
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
    aux->Pai = aux2;
    aux2->FilhoEsquerdo = aux;
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

Noh* AVL::ArrumarBalanceamento(Noh* aux){
    AtualizarAltura(aux);
    int FatorBal = FatorBalanceamento(aux);
    if((FatorBal >= -1) and (FatorBal <=1)){
        return aux;
    }
    if((FatorBal > 1) and (FatorBalanceamento(aux->FilhoEsquerdo) >= 0)){
        return RotacionarDireita(aux);
    }
    if((FatorBal > 1) and (FatorBalanceamento(aux->FilhoEsquerdo) < 0)){
        aux->FilhoEsquerdo = RotacionarEsquerda(aux->FilhoEsquerdo);
        return RotacionarDireita(aux);
    }
    if((FatorBal < -1) and (FatorBalanceamento(aux->FilhoDireito) <= 0)){
        return RotacionarEsquerda(aux);
    }
    if((FatorBal < -1) and (FatorBalanceamento(aux->FilhoDireito) > 0)){
        aux->FilhoDireito = RotacionarDireita(aux->FilhoDireito);
        return RotacionarEsquerda(aux);
    }
    return NULL;
}

void AVL::Inserir(int chave){
    Raiz = InserirAux(Raiz,chave);
}

Noh* AVL::InserirAux(Noh* aux,int chave){
    if(aux == NULL){
        Noh* novo = new Noh(chave);
        return novo;
    }else{
        if(chave < aux->Chave){
            aux->FilhoEsquerdo = InserirAux(aux->FilhoEsquerdo,chave);
            aux->FilhoEsquerdo->Pai = aux;
        }else{
            aux->FilhoDireito = InserirAux(aux->FilhoDireito,chave);
            aux->FilhoDireito->Pai = aux;
        }
    }
    return ArrumarBalanceamento(aux);
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
                cerr << "OpÃ§Ã£o invÃ¡lida\n";
        }
    } while (opcao != 'f');
    return 0;
}
        
