#include <iostream>

using namespace std;

void ABB::Transplanta(Noh* antigo,Noh* novo){
    if(antigo->Pai->FilhoDireito == antigo){
        antigo->Pai->FilhoDireito = novo;
    }else if (antigo->Pai->FilhoEsquerdo == antigo){
        antigo->Pai->FilhoEsquerdo = novo;
    }else if(antigo == Raiz){
        Raiz = novo;
    }
    if(novo != NULL){
        novo->Pai = antigo->Pai;
    }
}
