/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Nessa parte do código está contido os métodos da classe tabelaHash.
 */
#include "tabelaHash.h" //Aqui está a chamada do cabeçalho da classe tabelaHash, usado no 
//MakeFile.

using namespace std;

unsigned funcaoHash(int ID, int capacidade) { //Função usada para calcular o hash da estrutura.
  return ID % capacidade; //O hash é gerado pelo resto da divisão do ID pela capacidade. 
}

tabelaHash::tabelaHash(int cap) { //Construtor d tabelaHash.
  cadastro = new nohHash*[cap]; //Alocação da tabelaHash.
  capacidade = cap; //Atribuição da capacidade.
  for (int i = 0; i < cap; i++) //Inicializando as posições da tabela como NULL.
    cadastro[i] = NULL;
}

tabelaHash::~tabelaHash() { //Destrutor da tabelaHash.
  for (int i = 0; i < capacidade; i++) {
    nohHash* atual = cadastro[i];
    nohHash* anterior = NULL;
    while (atual != NULL) {
      anterior = atual;
      atual = atual->mProximo;
      delete anterior;
    }
  }
  delete[] cadastro; //Deletando a tabelaHash.
}

//Insere tabela Hash
void tabelaHash::Insere(int ID, long SALDO) { //Função usada para a inserção de dados na tabelaHash.
  unsigned pos = funcaoHash(ID, capacidade); //Chamada da funçãoHash.
  nohHash* novo = new nohHash(ID, SALDO);
  if (cadastro[pos] == NULL) {
    cadastro[pos] = novo;
  } else {
    nohHash* aux = cadastro[pos];
    while (aux->mProximo != NULL) {
      aux = aux->mProximo;
    }
    aux->mProximo = novo;
  }
}

//Percorre Imprimindo tabela Hash
void tabelaHash::Percorre() { //Função usada para o percorrimento da estrutura.
  //O percorrimento imprime a posição na Hash, o ID, e o Saldo.
  Serial.println();
  for (int i = 0; i < capacidade; i++) {
    nohHash* aux = cadastro[i];
    if (aux != NULL) {
      while (aux != NULL) {
        Serial.print(i);
        Serial.print(" : ID: ");
        Serial.print(aux->mDado.ID);
        Serial.print(" Saldo: R$");
        Serial.println(aux->mDado.Saldo);
        aux = aux->mProximo;
        Serial.println();
      }
    }
  }
  //  cout << endl;
}

//Remove ID da tabela Hash
bool tabelaHash::Remove(int remove) { //Função para remoção usada para remoção da estrutura.
  //A remoção é feita à partir de um ID, se o dado não for encontrado, ele dá erros.
  int pos = funcaoHash(remove, capacidade);
  if (cadastro[pos] != NULL and cadastro[pos]->mDado.ID == remove) {
    nohHash* atual = cadastro[pos];
    cadastro[pos] = cadastro[pos]->mProximo;
    delete atual;
    return true;
  } else {
    nohHash* anterior = cadastro[pos];
    nohHash* atual = cadastro[pos]->mProximo;
    while (atual != NULL and atual->mDado.ID != remove) {
      anterior = atual;
      atual = atual->mProximo;
    }
    if (atual != NULL and atual->mDado.ID == remove) {
      anterior->mProximo = atual->mProximo;
      delete atual;
      return true;
    } else {
      Serial.println("ERRO: Usuário não registrado.");
    }
  }
  return false;
}

//Busca um ID na tabela hash e atualiza seu saldo
//se estiver entre os 10 maiores saldos(Maior que ultimo Saldo da Fila)
void tabelaHash::Busca(int ID) { //Função usada para fazer uma busca na estrutura, se não
  //for encontrado nenhum resultado, ele dá um erro. Caso for encontrado, ele imprime o saldo.
  int pos = funcaoHash(ID, capacidade);
  bool encontrou = false;
  long valor = 0;
  nohHash* aux = NULL;
  if (cadastro[pos] == NULL) {
  } else {
    if (cadastro[pos]->mDado.ID == ID) {
      encontrou = true;
      aux = cadastro[pos];
      valor =  cadastro[pos]->mDado.Saldo;
    } else {
      aux = cadastro[pos];
      while (aux != NULL and aux->mDado.ID != ID) {
        aux = aux->mProximo;
      }
      if (aux != NULL) {
        if (aux->mDado.ID == ID) {
          encontrou = true;
          valor = aux->mDado.Saldo;
        }
      }
    }
    if (encontrou == true) {
      if (aux->mDado.Verifica == false) {
        if (MaioresSaldos.VerificaReajuste(aux->mDado.Saldo) == true) {
          aux->mDado.Saldo *= 1.1;
          aux->mDado.Verifica = true;
          valor = aux->mDado.Saldo;
        }
      }
    }
    //cout << endl;
  }
  if (encontrou == false) {
    Serial.println("ERRO: Usuário não registrado");
    Serial.println();
  } else if (encontrou == true) {
    Serial.print("Seu saldo é: R$");
    Serial.println(valor);
    Serial.println();
  }
}

void tabelaHash::InsereNaFila() { //Lê o arquivo com os 10 maiores saldos e insere na fila.
  MaioresSaldos.InsereFila();
  //MaioresSaldos.PercorreFila();
}
