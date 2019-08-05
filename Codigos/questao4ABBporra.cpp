#include <iostream>

using namespace std;

typedef int Dado;


class Noh{
    friend class Arvore;
    public:
      Noh* Pai;
      Noh* FilhoDireito;
      Noh* FilhoEsquerdo;
      Dado Valor;
      Noh(Dado d);
      ~Noh();  
};

Noh::Noh(Dado d){
    Pai = NULL;
    FilhoDireito = NULL;
    FilhoEsquerdo = NULL;
    Valor = d;
}

Noh::~Noh(){
    
}


class Arvore{
    private:
      Noh* Raiz;
      Noh* MinimoAux(Noh* aux);
      Noh* MaximoAux(Noh* aux);
      Noh* BuscaAux(Dado valor);
      void PercorreEmOrdemAux(Noh* aux);
      void PercorreEmPreOrdemAux(Noh* aux);
      void PercorreEmPosOrdemAux(Noh* aux);
    public:
      Arvore();
      ~Arvore();
      void Inserir(Dado valor);
      Dado Minimo();
      Dado Busca(Dado valor);
      void Transplanta(Noh* antigo,Noh* novo);
      void Remover(Dado valor);
      void PercorreEmOrdem();
      void PercorreEmPosOrdem();
      void PercorreEmPreOrdem();
      Dado Nivel(Dado valor);
      void Destrutor(Noh* aux);
      Dado Sucessor(Dado Sucede);
      Dado PaiSucessor(Noh* aux);
};

Noh* Arvore::MinimoAux(Noh* aux){
    while(aux->FilhoEsquerdo != NULL){
        aux = aux->FilhoEsquerdo;
    }
    return aux;
}

Noh* Arvore::MaximoAux(Noh* aux){
    while(aux->FilhoDireito != NULL){
        aux = aux->FilhoDireito;
    }
    return aux;
}

Noh* Arvore::BuscaAux(Dado valor){
    Noh* atual = Raiz;
    while(atual != NULL){
        if(atual->Valor == valor){
            return atual;
        }else if(atual->Valor > valor){
            atual = atual->FilhoEsquerdo;
        }else{
            atual = atual->FilhoDireito;
        }
    }
    return atual;
}

void Arvore::PercorreEmOrdemAux(Noh* aux){
    if(aux != NULL){
        PercorreEmOrdemAux(aux->FilhoEsquerdo);
        Dado Temp = Nivel(aux->Valor);
        cout << aux->Valor << '/' << Temp <<" ";
        PercorreEmOrdemAux(aux->FilhoDireito);
    }
}

void Arvore::PercorreEmPosOrdemAux(Noh* aux){
    if(aux != NULL){
        PercorreEmPosOrdemAux(aux->FilhoEsquerdo);
        PercorreEmPosOrdemAux(aux->FilhoDireito);
        Dado temp = Nivel(aux->Valor);
        cout << aux->Valor << '/' << temp <<" ";
    }
}

void Arvore::PercorreEmPreOrdemAux(Noh* aux){
    if(aux != NULL){
        cout <<'[' << aux->Valor << ']' <<" ";
        PercorreEmPreOrdemAux(aux->FilhoEsquerdo);
        PercorreEmPreOrdemAux(aux->FilhoDireito);
    }
}

void Arvore::Destrutor(Noh* aux){
    if(aux != NULL){
        Destrutor(aux->FilhoEsquerdo);
        Destrutor(aux->FilhoDireito);
        delete aux;
    }
}
    

Arvore::Arvore(){
    Raiz = NULL;
}

Arvore::~Arvore(){
    Destrutor(Raiz);
}

void Arvore::Inserir(Dado valor){
    Noh* teste = BuscaAux(valor);
    if(teste == NULL){
        Noh* novo = new Noh(valor);
        if(Raiz == NULL){
            Raiz = novo;
        }else{
            Noh* atual = Raiz;
            Noh* anterior = NULL;
            while(atual != NULL){
                anterior = atual;
                if(atual->Valor > valor){
                    atual = atual->FilhoEsquerdo;
                }else{
                    atual = atual->FilhoDireito;
                }   
            }
            novo->Pai = anterior;
            if(anterior->Valor > novo->Valor){
                anterior->FilhoEsquerdo = novo;
            }else{
                anterior->FilhoDireito = novo;
            }
        }
    }
}   

Dado Arvore::Minimo(){
    if(Raiz == NULL){
        cout << "ERRO" << endl;
    }
    Noh* minimo = MinimoAux(Raiz);
    return minimo->Valor;
}

Dado Arvore::Busca(Dado valor){
    Noh* procurado = BuscaAux(valor);
    if(procurado == NULL){
        cout << "ERRO" << endl;
    }
    return procurado->Valor;
}

void Arvore::Transplanta(Noh* antigo,Noh* novo){
    if(Raiz == antigo){
        Raiz = novo;
    }else if(antigo == antigo->Pai->FilhoEsquerdo){
        antigo->Pai->FilhoEsquerdo = novo;
    }else if(antigo == antigo->Pai->FilhoDireito){
        antigo->Pai->FilhoDireito = novo;
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}

void Arvore::Remover(Dado valor){
    Noh* Removido = BuscaAux(valor);
    if(Removido == NULL){
        cout << "ERRO" << endl;
    }else{
        if(Removido->FilhoEsquerdo == NULL){
            Transplanta(Removido,Removido->FilhoDireito);
        }else if(Removido->FilhoDireito == NULL){
            Transplanta(Removido,Removido->FilhoEsquerdo);
        }else{
            Noh* sucessor = MinimoAux(Removido->FilhoDireito);
            if(sucessor->Pai != Removido){
                Transplanta(sucessor,sucessor->FilhoDireito);
                sucessor->FilhoDireito = Removido->FilhoDireito;
                sucessor->FilhoDireito->Pai = sucessor;
            }
            Transplanta(Removido,sucessor);
            sucessor->FilhoEsquerdo = Removido->FilhoEsquerdo;
            sucessor->FilhoEsquerdo->Pai = sucessor;
        }
    }
    delete Removido;
}

void Arvore::PercorreEmOrdem(){
    PercorreEmOrdemAux(Raiz);
}

void Arvore::PercorreEmPosOrdem(){
    PercorreEmPosOrdemAux(Raiz);
}

void Arvore::PercorreEmPreOrdem(){
    PercorreEmPreOrdemAux(Raiz);
}

Dado Arvore::Nivel(Dado valor){
    Noh* aux = Raiz;
    Dado i = 0;
    if(aux->Valor == valor){
        return i;
    }else{
        while(aux->Valor != valor){
            if(valor > aux->Valor){
                aux  = aux->FilhoDireito;
            }else{
                aux  = aux->FilhoEsquerdo;
            }
            i++;
        }
    }
    return i;
}

Dado Arvore::Sucessor(Dado Sucede){
    Noh* aux = BuscaAux(Sucede);
    if(aux != NULL){
        if((aux->FilhoDireito != NULL) and (aux->FilhoDireito->FilhoEsquerdo == NULL)){
            cout << aux->FilhoDireito->Valor <<" ";
            return aux->FilhoDireito->Valor;
        }else if((aux->FilhoDireito != NULL) and (aux->FilhoDireito->FilhoEsquerdo != NULL)){
            cout << aux->FilhoDireito->FilhoEsquerdo->Valor <<" ";
            return aux->FilhoDireito->FilhoEsquerdo->Valor;
        }else{
            return PaiSucessor(aux);
        }
    }
    return 0;
}

Dado Arvore::PaiSucessor(Noh* aux){
    bool verifica = false;
    if(aux == Raiz){
        verifica = true;
        return 0;
    }else{
        if(verifica == false){
            if(aux->Pai->FilhoEsquerdo == aux){
                cout << aux->Pai->Valor <<" ";
                return aux->Pai->Valor;
                
            }else{
                aux = aux->Pai;
                return PaiSucessor(aux);
            }
        }
    }
    return 0;
}
        
        

    
int main(){
    Arvore Teste;
    char operacao;
    cin >> operacao;
    Dado valor;
    Dado busca;
    while(operacao != 'f'){
        switch(operacao){
            case 'i':
                cin >> valor;
                Teste.Inserir(valor);
                break;
            case 'r':
                cin >> busca;
                Teste.Remover(busca);
                break;
            case 'o':
                Teste.PercorreEmOrdem();
                break;
            case 'e':
                Teste.PercorreEmPreOrdem();
                break;
            case 's':
                Dado Sucede;
                cin >> Sucede;
                while(Sucede != 0){
                    Dado aux = Teste.Sucessor(Sucede);
                    Sucede = aux;
                }
                break;
        }
        cin >> operacao;
    }
    return 0;
}
