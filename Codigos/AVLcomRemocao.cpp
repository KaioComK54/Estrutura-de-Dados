#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

class NohAVL; // declaraÃ§Ã£o avanÃ§ada

typedef std::string TChave; // chave da Ã¡rvore
typedef float TValor; // valor da Ã¡rvore

// DeclaraÃ§Ãµes das classes ===================================================

class NohAVL {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    private:
        NohAVL (TChave c, const TValor& v);
        ~NohAVL();
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas tÃªm altura 1
};

class AVL {
    public:
        AVL();
        ~AVL();
        int InformaAltura(NohAVL* aux);
        void AtualizarAltura(NohAVL* aux);
        void DesalocarFilhosRecursivo(NohAVL* aux);
        int FatorBalanceamento(NohAVL* aux);
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
        void Remover(TChave texto);
        void Transplanta(NohAVL* antigo,NohAVL* novo);
    private:
        NohAVL* InserirRecursivo(NohAVL* ptNoh,TChave chave,const TValor& valor);
        NohAVL* RotacionarEsquerda(NohAVL* aux);
        NohAVL* RotacionarDireita(NohAVL* aux);
        NohAVL* ArrumarBalanceamento(NohAVL* aux);
        NohAVL* MinimoAux(NohAVL* aux);
        NohAVL* mPtRaiz;
        NohAVL* RemoverRecursivo(NohAVL* aux,TChave texto);
};

using namespace std;

NohAVL::NohAVL(TChave c, const TValor& v) {
    mChave = c;
    mValor = v;
    mPtEsq = NULL;
    mPtDir = NULL;
    mPtPai = NULL;
    mAltura = 1;
}

NohAVL::~NohAVL() {
    delete mPtEsq;
    delete mPtDir;
}

NohAVL* AVL::MinimoAux(NohAVL* aux){
    while(aux->mPtEsq != NULL){
        aux = aux->mPtEsq;
    }
    return aux;

}

NohAVL* AVL::ArrumarBalanceamento(NohAVL* aux) {
    AtualizarAltura(aux);
    int FatorBal = FatorBalanceamento(aux);
    if((FatorBal >= -1) and (FatorBal <= 1)){
        return aux;
    }
    if((FatorBal > 1) and (FatorBalanceamento(aux->mPtEsq) >= 0)){
        return RotacionarDireita(aux);
    }
    if((FatorBal > 1) and (FatorBalanceamento(aux->mPtEsq) < 0)){
        aux->mPtEsq = RotacionarEsquerda(aux->mPtEsq);
        return RotacionarDireita(aux);  
    }
    if((FatorBal < -1) and (FatorBalanceamento(aux->mPtDir) <= 0)){
        return RotacionarEsquerda(aux);
    }
    if((FatorBal < -1) and (FatorBalanceamento(aux->mPtDir) > 0)){
        aux->mPtDir = RotacionarDireita(aux->mPtDir);
        return RotacionarEsquerda(aux);
    }
    return NULL;
}

// Calcula e atualiza a altura de um nÃ³.
void AVL::AtualizarAltura(NohAVL* aux) {
    int AltArvEsq = InformaAltura(aux->mPtEsq);
    int AltArvDir = InformaAltura(aux->mPtDir);
    aux->mAltura = 1 + max(AltArvDir,AltArvEsq);
}

int AVL::InformaAltura(NohAVL* aux){
    if(aux == NULL){
        return 0;
    }
    AtualizarAltura(aux);
    return aux->mAltura;
}

// Desaloca todos os descendentes.
void AVL::DesalocarFilhosRecursivo(NohAVL* aux) {
    if(aux != NULL){
        DesalocarFilhosRecursivo(aux->mPtEsq);
        DesalocarFilhosRecursivo(aux->mPtDir);
        delete aux;
    }
}

// Calcula e retorna o fator de balanceamento do nÃ³.
int AVL::FatorBalanceamento(NohAVL* aux) {
    int AltArvEsq = InformaAltura(aux->mPtEsq);
    int AltArvDir = InformaAltura(aux->mPtDir);
    int FatorBal = AltArvEsq - AltArvDir;
    return FatorBal;
}

// Insere um nÃ³ numa subÃ¡rvore.
NohAVL* AVL::InserirRecursivo(NohAVL* ptNoh,TChave chave,const TValor& valor) {
    if(ptNoh == NULL){
        NohAVL* aux = new NohAVL(chave,valor);
        return aux;
    }else{
        if(chave > ptNoh->mChave){
            ptNoh->mPtDir = InserirRecursivo(ptNoh->mPtDir,chave,valor);
            ptNoh->mPtDir->mPtPai = ptNoh;
        }else{
            ptNoh->mPtEsq = InserirRecursivo(ptNoh->mPtEsq,chave,valor);
            ptNoh->mPtEsq->mPtPai = ptNoh;
        }
    }
    return ArrumarBalanceamento(ptNoh);
}


void AVL::Transplanta(NohAVL* antigo,NohAVL* novo){
    if(mPtRaiz == antigo){
        mPtRaiz = novo;
    }else if(antigo == antigo->mPtPai->mPtEsq){
        antigo->mPtPai->mPtEsq = novo;
    }else{
        antigo->mPtPai->mPtDir = novo;
    }
    if(novo != NULL){
        novo->mPtPai = antigo->mPtPai;
    }
}

// Rotaciona a subÃ¡rvore Ã  direita. Retorna a nova raiz da subÃ¡rvore.
NohAVL* AVL::RotacionarDireita(NohAVL* aux) {
    NohAVL* aux2 = aux->mPtEsq;
    aux->mPtEsq = aux2->mPtDir;
    if(aux2->mPtDir != NULL){
        aux2->mPtDir->mPtPai = aux;
    }
    aux2->mPtPai = aux->mPtPai;
    if(aux == mPtRaiz){
        mPtRaiz = aux2;
    }else if(aux == aux->mPtPai->mPtEsq){
        aux->mPtPai->mPtEsq = aux2;
    }else{
        aux->mPtPai->mPtDir = aux2;
    }
    aux2->mPtDir = aux;
    aux->mPtPai = aux2;
    AtualizarAltura(aux2);
    AtualizarAltura(aux);
    return aux2;
}

// Rotaciona a subÃ¡rvore Ã  esquerda. Retorna a nova raiz da subÃ¡rvore.
NohAVL* AVL::RotacionarEsquerda(NohAVL* aux) {
    NohAVL* aux2 = aux->mPtDir;
    aux->mPtDir = aux2->mPtEsq;
    if(aux2->mPtEsq != NULL){
        aux2->mPtEsq->mPtPai = aux;
    }
    aux2->mPtPai = aux->mPtPai;
    if(aux == mPtRaiz){
        mPtRaiz = aux2;
    }else if(aux == aux->mPtPai->mPtEsq){
        aux->mPtPai->mPtEsq = aux2;
    }else{
        aux->mPtPai->mPtDir = aux2;
    }
    aux2->mPtEsq = aux;
    aux->mPtPai = aux2;
    AtualizarAltura(aux2);
    AtualizarAltura(aux);
    return aux2;
}

// Escreve o conteÃºdo de um nÃ³ no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}


AVL::AVL() {
    mPtRaiz = NULL;
}

AVL::~AVL() {
    delete mPtRaiz;
}

void AVL::Remover(TChave texto){
    if(mPtRaiz == NULL){
        cerr << "Tentativa de remover elemento de uma Ã¡rvore vazia." << endl;
    }else{
        mPtRaiz = RemoverRecursivo(mPtRaiz,texto);
    }
}

NohAVL* AVL::RemoverRecursivo(NohAVL* aux,TChave texto){
    if(aux == NULL){
        cerr << "Erro na Remocao" << endl;
    }else{
        if(texto > aux->mChave){
            aux->mPtDir = RemoverRecursivo(aux->mPtDir,texto);
        }else if(texto < aux->mChave){
            aux->mPtEsq = RemoverRecursivo(aux->mPtEsq,texto);
        }else{
            NohAVL* RaizSubArvore = NULL;
            if(aux->mPtEsq == NULL){
                RaizSubArvore = aux->mPtDir;
                Transplanta(aux,aux->mPtDir);
            }else if(aux->mPtDir == NULL){
                RaizSubArvore = aux->mPtEsq;
                Transplanta(aux,aux->mPtEsq);
            }else{
                NohAVL* sucessor = MinimoAux(aux->mPtDir);
                RaizSubArvore = sucessor;
                if(sucessor->mPtPai != aux){
                    Transplanta(sucessor,sucessor->mPtDir);
                    NohAVL* aux2 = sucessor->mPtPai;
                    while(aux2 != aux->mPtDir){
                        AtualizarAltura(aux2);
                        aux2 = aux2->mPtPai;
                    }
                    sucessor->mPtDir = ArrumarBalanceamento(aux->mPtDir);
                    sucessor->mPtDir->mPtPai = sucessor;
                }
                Transplanta(aux,sucessor);
                sucessor->mPtEsq = aux->mPtEsq;
                sucessor->mPtEsq->mPtPai = sucessor;
            }
            delete aux;
            if(RaizSubArvore == NULL){
                return RaizSubArvore;
            }else{
                return ArrumarBalanceamento(RaizSubArvore);
            }
        }
    }
    return NULL;
}
                    
                    
// Escreve o conteÃºdo da Ã¡rvore nÃ­vel a nÃ­vel, na saÃ­da de dados informada.
// Usado para conferir se a estrutra da Ã¡rvore estÃ¡ correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nÃ³ especial para marcar fim de um nÃ­vel
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
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
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

// Insere um par chave/valor na Ã¡rvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    mPtRaiz = InserirRecursivo(mPtRaiz,chave,valor);
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'r':
                cin >> chave;
                minhaArvore.Remover(chave);
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
