#include <iostream>

using namespace std;

void FuncaoHash(int valor,int posicoes,int& Posicao){
    Posicao = valor%posicoes;
}

class Hash{
    private:
        int* VetorDados;
        int Capacidade;
        int Tamanho;
    public:
        Hash();
        ~Hash();
        void Inserir(int valor);
        void Remover(int valor);
        void Redimensiona();
        void Escrever();
};

Hash::Hash(){
    VetorDados = new int[5];
    Capacidade = 5;
    Tamanho = 0;
}

Hash::~Hash(){
    delete[] VetorDados;
    Capacidade = 0;
    Tamanho = 0;
}

void Hash::Inserir(int valor){
    if(Tamanho < Capacidade){
        VetorDados[Tamanho] = valor;
        Tamanho++;
    }else if(Tamanho == Capacidade){
        Redimensiona();
        VetorDados[Tamanho] = valor;
        Tamanho++;
    }
}

void Hash::Remover(int valor){
    int* aux = new int[Tamanho-1];
    int posicao = 0;
    bool condicao = false;
    for(int i = 0;i < Tamanho;i++){
        if(VetorDados[i] == valor and condicao == false){
            posicao = i;
            condicao = true;
        }
    }
    for(int i = posicao;i < Tamanho;i++){
        if((i+1) < Tamanho){
            swap(VetorDados[i],VetorDados[i+1]);
        }
    }
    for(int i = 0;i < Tamanho-1;i++){
        aux[i] = VetorDados[i];
    }
    delete[] VetorDados;
    VetorDados = new int[Tamanho-1];
    for(int i = 0;i < Tamanho;i++){
        VetorDados[i] = aux[i];
    }
    delete[] aux;
    Capacidade = Capacidade-1;
    Tamanho = Tamanho-1;
}

void Hash::Redimensiona(){
    int* aux = new int[Capacidade+5];
    for(int i = 0;i < Tamanho;i++){
        aux[i] = VetorDados[i];
    }
    delete[] VetorDados;
    Capacidade += 5;
    VetorDados = new int[Capacidade+5];
    for(int i = 0;i < Tamanho;i++){
        VetorDados[i] = aux[i];
    }
    delete[] aux;
}

void Hash::Escrever(){
    cout << '[' <<" ";
    for(int i = 0;i < Tamanho;i++){
        if(i < Tamanho-1){
            cout << VetorDados[i] <<" "<<','<<" ";
        }else if(i == Tamanho-1){
            cout << VetorDados[i];
        }
    }
    cout <<" "<<']'<< endl;
}

int main(){
    int Tamanho;
    cin >> Tamanho;
    Hash* Teste = new Hash[Tamanho];
    int Valor;
    int Posicao = 0;
    char opcao;
    do{
        cin >> opcao;
        switch(opcao){
            case 'i':
                cin >> Valor;
                FuncaoHash(Valor,Tamanho,Posicao);
                Teste[Posicao].Inserir(Valor);
                break;
            case 'r':
                cin >> Valor;
                FuncaoHash(Valor,Tamanho,Posicao);
                Teste[Posicao].Remover(Valor);
                break;
            case 'e':
                for(int i = 0;i < Tamanho;i++){
                    Teste[i].Escrever();
                }
                break;
            case 'f':
                break;
            default:
                cerr << "Opcao Invalida" << endl;
            }
    }while(opcao != 'f');
    return 0;
}


