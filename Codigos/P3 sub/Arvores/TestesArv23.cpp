#include <iostream>
#include <queue>

typedef int TChave;

class Noh {
    friend class Arvore23;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    protected:
        // Métodos
        Noh(const TChave& chave, Noh* ptPai);
        ~Noh();
        void DesalocarRecursivo();
        void DividirSeNecessario(Noh** ptPtRaiz);
        void InserirLocal(const TChave& chave, Noh* ptFilho);
        void InserirRecursivo(const TChave& chave, Noh** ptPtRaiz);
        // Atributos
        TChave mChaves[3]; // 3 chaves só temporariamente
        Noh* mFilhos[4];   // 4 filhos só temporariamente
        Noh* mPtPai;
        short int mQtdChaves;
        int mID; // identificador, útil para debugar o programa
};

Noh::~Noh(){
    if(this->mFilhos[0] != NULL){
        for(int i = 0;i < 4;i++){
            delete mFilhos[i];
        }
    }
    delete this;
}

class Arvore23 {
    public:
        Arvore23();
        ~Arvore23();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(const TChave& chave);
    protected:
        Noh* mPtRaiz;
};

using namespace std;

// === Classe Noh ==============================================================
Noh::Noh(const TChave& chave, Noh* ptPai) {
    mChaves[0] = chave;
    mQtdChaves = 1;
    mFilhos[0] = NULL; // usamos o primeiro filho para identificar folha
    mPtPai = ptPai;
    static int contador = 1;
    mID = contador++;
}


void Noh::DesalocarRecursivo() {
    if (mFilhos[0] != NULL)
        for (int i = 0; i <= mQtdChaves; ++i)
            mFilhos[i]->DesalocarRecursivo();
    delete this;
}

void Noh::DividirSeNecessario(Noh** ptPtRaiz) {
    if(mQtdChaves > 2){
        Noh* dividido = new Noh(mChaves[mQtdChaves-1],mPtPai);
        if(mFilhos[2] != NULL){
            dividido->mFilhos[0] = mFilhos[2];
            dividido->mFilhos[0]->mPtPai = dividido;
            mFilhos[2] = NULL;
        }
        if(mFilhos[3] != NULL){
            dividido->mFilhos[1] = mFilhos[3];
            dividido->mFilhos[1]->mPtPai = dividido;
            mFilhos[3] = NULL;
        }
        mQtdChaves = 1;
        if(mPtPai != NULL){
            mPtPai->InserirLocal(mChaves[1],dividido);
            mPtPai->DividirSeNecessario(ptPtRaiz);
        }else{
            Noh* novoPai = new Noh(mChaves[1],NULL);
            mPtPai = novoPai;
            dividido->mPtPai = novoPai;
            novoPai->mFilhos[0] = this;
            novoPai->mFilhos[1] = dividido;
            *ptPtRaiz = novoPai;
        }
    }
}

void Noh::InserirLocal(const TChave& chave, Noh* ptFilho) {
    int pos = mQtdChaves-1;
    for(int i = 2;i > pos;i--){
        while(pos > 0 and mChaves[pos] > chave){
            pos--;
        }
        mChaves[pos+1] = mChaves[pos];
        mFilhos[pos+2] = mFilhos[pos+1];
    }
    mChaves[pos+1] = chave;
    mFilhos[pos+2] = ptFilho;
    mQtdChaves++;
}


void Noh::InserirRecursivo(const TChave& chave, Noh** ptPtRaiz) {
    int pos = mQtdChaves;
    if(mFilhos[0] == NULL){
        while(pos > 0 and mChaves[pos-1] > chave){
            mChaves[pos] = mChaves[pos-1];
            pos--;
        }
        mChaves[pos] = chave;
        mQtdChaves++;
    }else{
        while(pos > 0 and mChaves[pos-1] > chave){
            pos--;
        }
        mFilhos[pos]->InserirRecursivo(chave,ptPtRaiz);
    }
    DividirSeNecessario(ptPtRaiz);
}


ostream& operator<<(ostream& saida, Noh* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else {
        saida << '[' << ptNoh->mID << "|" << ptNoh->mChaves[0];
        for (int i = 1; i < ptNoh->mQtdChaves; ++i)
            saida << ',' << ptNoh->mChaves[i];
        int pai = (ptNoh->mPtPai == NULL) ? 0 : ptNoh->mPtPai->mID;
        saida << "|" << pai << ';';
        if (ptNoh->mFilhos[0] != NULL) {
            saida << ptNoh->mFilhos[0]->mID;
            for (int i = 1; i <= ptNoh->mQtdChaves; ++i)
                saida << ',' << ptNoh->mFilhos[i]->mID;
        }
        saida << ']';
    }
    return saida;
}

// === Classe Arvore23 =========================================================
Arvore23::Arvore23() : mPtRaiz(NULL) {
}

Arvore23::~Arvore23() {
    if (mPtRaiz != NULL){
        delete mPtRaiz;
    }
}

// Escreve a árvore nível a nível para facilitar a depuração.
void Arvore23::EscreverNivelANivel(ostream& saida) {
    if (mPtRaiz == NULL)
        cout << "[]\n";
    else {
        queue<Noh*> filhos;
        filhos.push(mPtRaiz);
        while (not filhos.empty()) {
            unsigned nroNohsNesteNivel = unsigned(filhos.size());
            for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
                Noh* ptNoh = filhos.front();
                filhos.pop();
                saida << ptNoh << ' ';
                if (ptNoh->mFilhos[0] != NULL)
                    for (short int i = 0; i <= ptNoh->mQtdChaves; ++i)
                        filhos.push(ptNoh->mFilhos[i]);
            }
            cout << "\n";
        }
    }
}

// Insere uma chave na árvore.
void Arvore23::Inserir(const TChave& chave) {
    if (mPtRaiz == NULL){
        mPtRaiz = new Noh(chave, NULL);
    } else {
        mPtRaiz->InserirRecursivo(chave, &mPtRaiz);
    }
}

// === Programa ================================================================
int main() {
    Arvore23* arvore = new Arvore23();
    char opcao;
    TChave chave;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave;
                arvore->Inserir(chave);
                break;
            case 'e': // Escrever nós nível a nível
                arvore->EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                delete arvore;
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
