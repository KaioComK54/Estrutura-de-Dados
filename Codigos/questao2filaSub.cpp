#include <iostream>

typedef int Dado;

class Fila {
    public:
        Fila(unsigned cap = 80);
        ~Fila();
        // Remove e retorna o primeiro elemento da fila.
        Dado Desenfileira();
        // Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente
        // realizada.
        bool Enfileirar(const Dado& valor);
        // Escreve todo o conteÃºdo do armazenamento da fila na saÃ­da de dados.
        void EscreverConteudo(std::ostream& saida) const;
        // Retorna tamanho, capacidade, inicio e fim da fila.
        void Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const;
        // Retorna o primeiro elemento da fila, sem removÃª-lo.
        Dado Proximo() const;
        // Retorna a quantidade de elementos na fila.
        unsigned Tamanho() const { return mTamanho; }
        // Consulta se a fila estÃ¡ vazia.
        bool Vazia() const;
    protected:
        unsigned mCapacidade;
        Dado* mDados;
        unsigned mPosInicio; // indica a posicao do primeiro
        unsigned mPosFim;    // indica a posicao do ultimo
        unsigned mTamanho;
};

using namespace std;

Fila::Fila(unsigned cap) { // cap tem valor default
    mCapacidade = cap;
    mDados = new Dado[mCapacidade];
    mPosInicio = 0;
    mPosFim = 0;
    mTamanho = 0;
}

Fila::~Fila() {
    delete[] mDados;
    mTamanho = 0;
}

// Remove e retorna o primeiro elemento da fila.
Dado Fila::Desenfileira() {
}

// Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente realizada.
bool Fila::Enfileirar(const Dado& valor) {
        
}

// Escreve todo o conteÃºdo do armazenamento (comeÃ§ando da posiÃ§Ã£o zero) da fila na saÃ­da de dados.
void Fila::EscreverConteudo(ostream& saida) const {
}

// Retorna tamanho, capacidade, inicio e fim da fila.
void Fila::Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const {
}

// Retorna o primeiro elemento da fila, sem removÃª-lo.
Dado Fila::Proximo() const {
}

// Consulta se a fila estÃ¡ vazia.
bool Fila::Vazia() const {
    if(mTamanho == 0){
        return true;
    }else{
        return false;
    }
}

int main() {
    unsigned tamanho, capacidade, inicio, fim;
    cin >> capacidade;
    Fila fila(capacidade);
    Dado valor;
    char comando;
    cin >> comando;
    while (comando != 't') {
        switch (comando) {
        case 'e': // enfileirar
            cin >> valor;
            if (not fila.Enfileirar(valor))
                cout << "FILA CHEIA!\n";
            break;
        case 'd': // desenfileirar
            if (fila.Vazia())
                cout << "ERRO\n";
            else {
                valor = fila.Desenfileira();
                cout << valor << endl;
            }
            break;
        case 'p': // proximo
            if (fila.Vazia())
                cout << "ERRO\n";
            else
                cout << fila.Proximo() << endl;
            break;
        case 'i': // informaÃ§Ãµes sobre a fila
            fila.Info(&tamanho, &capacidade, &inicio, &fim);
            cout << "tamanho=" << tamanho << " capacidade=" << capacidade << " inicio=" << inicio
                 << " fim=" << fim << endl;
            fila.EscreverConteudo(cout);
            break;
        case 't':
            // vai testar novamente no while
            break;
        default:
            cout << "comando invÃ¡lido\n";
        }
        cin >> comando;
    }
    return 0;
}
