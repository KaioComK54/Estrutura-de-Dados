#include <iostream>

using namespace std;

class Fila{
    private:
        unsigned Tamanho;
        unsigned Capacidade;
        unsigned PosFim;
        unsigned PosInicio;
        int* Dados;
    public:
        Fila(int cap);
        ~Fila();
        bool Enfileira(int valor);
        int Desenfileira();
        void Info(unsigned &Tam,unsigned &Cap,unsigned &PosF,unsigned &PosI);
        int Proximo();
        unsigned RetornaTamanho();
        void Escrever();
};

Fila::Fila(int cap){
    Capacidade = cap;
    Tamanho = 0;
    PosFim = 0;
    PosInicio = 0;
    Dados = new int[cap];
}

Fila::~Fila(){
    delete Dados;
}

bool Fila::Enfileira(int valor){
    if(Tamanho < Capacidade){
        if(Tamanho == 0){
            Dados[Tamanho] = valor;
            Tamanho++;
            PosFim++;
        }else if(Tamanho > 0 and PosFim < Capacidade-1){
            Dados[Tamanho] = valor;
            PosFim = Tamanho;
            Tamanho++;
        }else if(Tamanho > 0 and PosFim == Capacidade-1){
            Dados[Tamanho] = valor;
            Tamanho++;
            PosFim = 0;
        }
        return true;
    }
    return false;
}

int Fila::Desenfileira(){
    int valor = 0;
    if(PosInicio < PosFim){
        valor = Dados[PosInicio];
        PosInicio++;
        Tamanho--;
    }else if(PosInicio == PosFim){
        valor = Dados[PosInicio];
        Tamanho--;
        PosInicio = 0;
        PosFim = 0;
    }else if(PosInicio > PosFim and PosInicio < Capacidade-1){
        valor = Dados[PosInicio];
        Tamanho--;
        PosInicio++;
    }else if(PosInicio > PosFim and PosInicio == Capacidade-1){
        valor = Dados[PosInicio];
        Tamanho--;
        PosInicio = 0;
    }
    return valor;
}

void Fila::Escrever(){
    for(unsigned i = 0;i < Tamanho;i++){
        cout << Dados[i] <<" ";
    }
    cout << endl;
}

void Fila::Info(unsigned &Tam,unsigned &Cap,unsigned &PosF,unsigned &PosI){
    Tam = Tamanho;
    Cap = Capacidade;
    PosF = PosFim;
    PosI = PosInicio;
}

int Fila::Proximo(){
    return Dados[PosInicio];
}

unsigned Fila::RetornaTamanho(){
    return Tamanho;
}

int main(){
    Fila Teste(5);
    int valor;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> valor;
                Teste.Enfileira(valor);
                if(not Teste.Enfileira(valor)){
                    cerr << "Fila Cheia" << endl;
                }
                break;
            case 'r':
                if(Teste.RetornaTamanho() != 0){
                    int dado = Teste.Desenfileira();
                    cout << dado << endl;
                }else{
                    cerr << "Fila Vazia" << endl;
                }
                break;
            case 'd':
                unsigned tam = 0;
                unsigned cap = 0;
                unsigned posf = 0;
                unsigned posi = 0;
                Teste.Info(tam,cap,posf,posi);
                cout << "Tamanho : " << tam << endl;
                cout << "Capacidade : " << cap << endl;
                cout << "Posicao Inicial : " << posi << endl;
                cout << "Posicao Final : " << posf << endl;
                break;
            case 'f':
                break;
            default:
                cerr << "Escolha Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}
