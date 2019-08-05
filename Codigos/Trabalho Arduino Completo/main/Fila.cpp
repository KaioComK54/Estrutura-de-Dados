/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Este trabalho contém os Arquivos:  
 * maiores.txt ==> Este arquivo contém os 10 maiores saldos do banco de dados que serão lidos e inseridos em
 * uma fila.
 * Essa parte do código é onde fica a classe fila sem o cabeçalho dos métodos.
 */

#include "Arduino.h" //Biblioteca usada especialmente para o MakeFile, ela é usada para usar os 
//comandos padrões do arduino, como a serial por exemplo.
#include "Fila.h" //Usado para adicionar a classe fila para que essa classe seje contruida, espe
//cial do MakeFile.

using namespace std;

Fila::Fila() { //Construtor da Fila.
  PrimeiroFila = NULL; //Ponteiro para o primeiro dado da fila.
  UltimoFila = NULL; //Ponteiro para o ultimo dado da fila.
}

Fila::~Fila() { //Destrutor da Fila.
  nohFila* anterior = NULL;
  nohFila* atual = PrimeiroFila;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->AnteriorFila;
    delete anterior;
  }
  delete PrimeiroFila;
  delete UltimoFila;
}

//Insere Saldo na Fila
void Fila::InsereFila() { //Método usado para inserir os dados do arquivo "maiores.txt" na fila.
  long Saldo;
  ifstream filaS("maiores.txt"); //Abrindo o arquivo "maiores.txt".
  if (!filaS.is_open()) { //Testando a abertura do arquivo "maiores.txt".
    Serial.println("ERRO NA ABERTURA");
  } else {
    while (!filaS.eof()) { //Repetição para o tratamento de dados na leitura do arquivo "maiores.txt"
      //Tratamentos da inserção na Fila.
      filaS >> Saldo;
      filaS.skipWhite(); //Usado para pular caracteres brancos.
      nohFila* novo = new nohFila(Saldo);
      if (novo) {
        if (PrimeiroFila == NULL) {
          PrimeiroFila = novo;
          UltimoFila = novo;
        } else {
          UltimoFila->AnteriorFila = novo;
          UltimoFila = novo;
        }
      }
    }
    filaS.close(); //Fechando o arquivo.
  }
}

//Percorre imprimindo a fila
void Fila::PercorreFila() { //Método utilizado para percorrer os dados da classe fila.
  nohFila* atual = PrimeiroFila;
  while (atual != NULL) {
    Serial.println(atual->SaldoFila);
    atual = atual->AnteriorFila;
  }
}

//Verifica se o Saldo esta entre os 10 maiores
bool Fila::VerificaReajuste(long Saldo) {
  if (Saldo >= UltimoFila->SaldoFila) {
    return true;
  }
  return false;
}
