#include <iostream>
#include <stdexcept>
#include <queue>

typedef std::string TValor;
typedef unsigned TChave;
enum Cor {PRETO, VERMELHO};

class Noh {
    friend class ArvoreRN;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    public:
        Noh(unsigned chave, TValor valor);
    private:
        Noh* Tio();
        void DesalocarRecursivo();
        TValor mValor;
        TChave mChave;
        Cor mCor;
        Noh* mEsq;
        Noh* mDir;
        Noh* mPai;
};

class ArvoreRN {
    public:
        ArvoreRN();
        ~ArvoreRN();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(unsigned chave, TValor valor);
    private:
        void ArrumarInsercao(Noh* umNoh);
        void RotacionarDireita(Noh* umNoh);
        void RotacionarEsquerda(Noh* umNoh);
        Noh* mRaiz;
};

using namespace std;

// === classe Noh ==============================================================
Noh::Noh(TChave chave, TValor valor)
    : mValor(valor), mChave(chave), mCor(VERMELHO), mEsq(NULL), mDir(NULL), mPai(NULL) {
}

// Desaloca as subÃ¡rvores e depois a si prÃ³prio.
void Noh::DesalocarRecursivo() {
    if(this->mEsq != NULL){
        this->mEsq->DesalocarRecursivo();
    }
    if(this->mDir != NULL){
        this->mDir->DesalocarRecursivo();
    }
    delete this;
}

// Retorna o tio do nÃ³, ou NULL se nÃ£o houver tio
Noh* Noh::Tio() {
    if(this->mPai->mPai->mEsq == this->mPai){
        if(this->mPai->mPai->mDir != NULL){
            return this->mPai->mPai->mDir;
        }
    }else if(this->mPai->mPai->mDir == this->mPai){
        if(this->mPai->mPai->mEsq != NULL){
            return this->mPai->mPai->mEsq;
        }
    }
    return NULL;
}

// === classe ArvoreRN =========================================================
ArvoreRN::ArvoreRN() : mRaiz(NULL) {
}

ArvoreRN::~ArvoreRN() {
    delete mRaiz;
}

// insere uma chave/valor na Ã¡rvore,
// chama ArrumarInsercao para corrigir eventuais problemas
void ArvoreRN::Inserir(unsigned chave, TValor valor) {
    Noh* aux = new Noh(chave,valor);
    if(mRaiz == NULL){
        aux->mCor = PRETO;
        mRaiz = aux;
    }else{
        Noh* atual = mRaiz;
        Noh* anterior;
        while(atual != NULL){
            anterior = atual;
            if(atual->mChave > chave){
                atual = atual->mEsq;
            }else{
                atual = atual->mDir;
            }
        }
        aux->mPai = anterior;
        if(anterior->mChave > aux->mChave){
            anterior->mEsq = aux;
        }else{
            anterior->mDir = aux;
        }
    }
    ArrumarInsercao(aux);
}

// procedimento para manter balanceamento apÃ³s inserÃ§Ã£o
void ArvoreRN::ArrumarInsercao(Noh* umNoh) {
     Noh* tio;
    while(umNoh != mRaiz and umNoh->mPai->mCor == VERMELHO){
        if(umNoh->mPai != mRaiz){
            tio = umNoh->Tio();
        }
        else{
            tio = NULL;
        }
        if(tio != NULL and tio->mCor == VERMELHO){
            tio->mCor = PRETO;
            umNoh->mPai->mCor = PRETO;
            umNoh->mPai->mPai->mCor = VERMELHO;
            umNoh = umNoh->mPai->mPai;
        }
        else{
            ///Caso EE
            if(umNoh->mPai == umNoh->mPai->mPai->mEsq and umNoh == umNoh->mPai->mPai){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai->mPai);
                continue;
            }
            ///Caso ED
            if(umNoh->mPai == umNoh->mPai->mPai->mEsq and umNoh == umNoh->mPai->mDir){
                umNoh = umNoh->mPai;
                RotacionarEsquerda(umNoh);
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai->mPai);
                continue;
            }
            ///Caso DD
            if(umNoh->mPai == umNoh->mPai->mPai->mDir and umNoh == umNoh->mPai->mDir){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai->mPai);
                continue;
            }
            ///Caso DE
            if(umNoh->mPai == umNoh->mPai->mPai->mDir and umNoh == umNoh->mPai->mEsq){
                umNoh = umNoh->mPai;
                RotacionarDireita(umNoh);
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai->mPai);
                continue;
            }
        }
    }
    mRaiz->mCor = PRETO;
}

// rotaÃ§Ã£o Ã  esquerda, muda a raiz se necessÃ¡rio
void ArvoreRN::RotacionarEsquerda(Noh* umNoh) {
    Noh* aux = umNoh->mDir;
    umNoh->mDir = aux->mEsq;
    if(aux->mEsq != NULL){
        aux->mEsq->mPai = umNoh;
    }
    aux->mPai = umNoh->mPai;
    if(umNoh == mRaiz){
        mRaiz = aux;
    }else if(umNoh == umNoh->mPai->mEsq){
        umNoh->mPai->mEsq = aux;
    }else{
        umNoh->mPai->mDir = aux;
    }
    aux->mEsq = umNoh;
    umNoh->mPai = aux;
}

// rotaÃ§Ã£o Ã  direita, muda a raiz se necessÃ¡rio
void ArvoreRN::RotacionarDireita(Noh* umNoh) {
    Noh* aux = umNoh->mEsq;
    umNoh->mEsq = aux->mDir;
    if(aux->mDir != NULL){
        aux->mDir->mPai = umNoh;
    }
    aux->mPai = umNoh->mPai;
    if(umNoh == mRaiz){
        mRaiz = aux;
    }else if(umNoh == umNoh->mPai->mEsq){
        umNoh->mPai->mEsq = aux;
    }else{
        umNoh->mPai->mDir = aux;
    }
    aux->mDir = umNoh;
    umNoh->mPai = aux;   
}

// Escreve o conteÃºdo da Ã¡rvore nÃ­vel a nÃ­vel
void ArvoreRN::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    filhos.push(mRaiz);
    while (not filhos.empty()) {
        unsigned nroNohsNesteNivel = unsigned(filhos.size());
        for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
            Noh* ptNoh = filhos.front();
            filhos.pop();
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mEsq);
                filhos.push(ptNoh->mDir);
            }
        }
        cout << "\n";
    }
}

// Escreve um nÃ³ (ou NIL).
ostream& operator<<(ostream& saida, Noh* ptNoh) {
    static char vetLetrasCores[] = "PV";
    if (ptNoh == NULL)
        saida << "NIL";
    else
        saida << '[' << vetLetrasCores[ptNoh->mCor] << ':' << ptNoh->mChave << '/'
              << ptNoh->mValor << ']';
    return saida;
}

int main() {
    ArvoreRN arvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                arvore.Inserir(chave, valor);
                break;
            case 'e': // Escrever nÃ³s nÃ­vel a nÃ­vel
                arvore.EscreverNivelANivel(cout);
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
