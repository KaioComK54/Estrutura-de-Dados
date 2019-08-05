#include <iostream>
#include <queue>

typedef int TChave;

class Noh {
    friend class Arvore23;
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    protected:
        // Métodos
        Noh(const TChave& chave, Noh* ptPai);
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

Noh::Noh(const TChave& chave, Noh* ptPai){
    mChaves[0] = chave;
    mPtPai = ptPai;
    mQtdChaves = 1;
    mFilhos[0] = NULL;
    static int contador = 1;
    mID = contador++;
}

void Noh::DesalocarRecursivo(){
    if(mFilhos[0] != NULL){
        for(int i=0;i<mQtdChaves;i++){
            mFilhos[i]->DesalocarRecursivo();
        }
    }
    delete this;
}

void Noh::DividirSeNecessario(Noh** ptPtRaiz) {
    if(mQtdChaves > 2){
        Noh* dividido = new Noh(mChaves[mQtdChaves-1], mPtPai);
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
            mPtPai->InserirLocal(mChaves[1], dividido);
            mPtPai->DividirSeNecessario(ptPtRaiz);
        } else {
            Noh* novoPai = new Noh(mChaves[1], NULL);
            mPtPai = novoPai;
            dividido->mPtPai = novoPai;
            novoPai->mFilhos[0] = this;
            novoPai->mFilhos[1] = dividido;
            *ptPtRaiz = novoPai;
        }
    }
}

void Noh::InserirLocal(const TChave& chave, Noh* ptFilho){
    int pos = mQtdChaves-1;
    for(int i=2;i>=0;i--){
        if(pos >= 0 and mChaves[pos] > chave){
            pos--;
        }
        mChaves[i] = mChaves[i-1];
        mFilhos[i+1] = mFilhos[i];
    }
    mChaves[pos+1] = chave;
    mFilhos[pos+2] = ptFilho;
    mQtdChaves++;
}

void Noh::InserirRecursivo

