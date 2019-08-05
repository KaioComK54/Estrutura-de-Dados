/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Este trabalho contém os Arquivos:  
 * Cadastros.txt ==> Este arquivo funciona como um banco de dados que será inserida na estrutura principal.
 * maiores.txt ==> Este arquivo contém os 10 maiores saldos do banco de dados que serão lidos e inseridos em
 * uma fila.
 */

#include <SPI.h> //Usada para trocar informações via serial com os periféricos do Arduino.
#include "SdFat.h" //Usada para a manipulação do Módulo SD, usada para tratamento de arquivo.
#include "tabelaHash.h" //Essa é a parte do Makefile que inclui a classe Hash na main para que
//o objeto da classe tabelaHash "TH" possa ser criado. 
#include "Fila.h" //Essa é a parte do Makefile que inclui a classe Fila na classe tabelaHash
//para que seje armazenado os 10 maiores que estarão dentro do atributo Maiores saldos.

const uint8_t chipSelect = 4; //Pino 4 setado para o funcionamento do Módulo SD.

SdFat sd; //Objeto do arquivo do sistema.

//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt(F(s)) //Define erros de funcionamento do SD card.

using namespace std;

tabelaHash TH(40); //Constrói uma tabelaHash

void setup() {
  Serial.begin(9600); //Inicializa o Serial do Arduino.
  SPI.begin(); 
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) { // Checa se o pino do SD card foi cetado com sucesso.
    sd.initErrorHalt();
  }
  int ID; //Variável utilizada para armazenar o ID que estará no arquivo para a tranferência da
  //identificação dos cadastros.
  long Saldo; //Variável utilizada para armazenar os Saldos que estará no arquivo para a tranferência da
  //identificação dos cadastros.
 
  ifstream sdin("cadastro.txt"); //Abertura do arquivo cadastros.txt para leitura
  
  if (!sdin.is_open()) { //Checar se o SD card foi utilizado.
  }

  while (!sdin.eof()) { //Estrutura de repetição para a leitura dos dados.
    sdin >> ID;
    sdin.skipWhite(); //Usado para pular caracteres Brancos.
    sdin >> Saldo;
    sdin.skipWhite();
    TH.Insere(ID, Saldo);
  }
  
  sdin.close(); //Fechamento do arquivo.

  TH.InsereNaFila(); //Chamada da função de inserção na Fila.

  Serial.println();

  //Setando os pinos Analógicos e Digitais para o uso dos Led's e dos botões:
  //A0, A1, A2 e A3 para os botões
  //2, 3, 8 e 9 para os leds
 
  pinMode(A0, INPUT_PULLUP); 
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}


void loop() {
  //Aqui inicializa o loop do Arduino, local onde será feita as operações de menu
  //ofertadas pelos botões.
  if (digitalRead(A3) == 0) { //Essa condição é usada para acesso ao método de percorrimento.
    digitalWrite(9, HIGH); //Setando a saida do pino 9 como alta para acender o Led branco.
    TH.Percorre(); //Chamada do método.
    delay(1000);
    digitalWrite(9, LOW);//desligando o Led branco.
  }
  int idBusca; //Variável utilizada para armazenar o dado Buscado.
  int IdInsercao; //Variável utilizada para armazenar o dado ID para inserção.
  long SaldoInsercao = 500;
  if (digitalRead(A1) == 0) { //Essa condição acessa a busca da estrutura.
    digitalWrite(3, HIGH); //setando o pino 3 como alto para acender o Led amarelo.
    Serial.println("Digite um ID a ser buscado: ");
    delay(5000);
    idBusca = Serial.parseInt(); //Recebendo o dado do serial para a busca.
    TH.Busca(idBusca); //Buscando o dado recebido para tratar inserção sem repetição.
    Serial.println();
    digitalWrite(3, LOW); //desligando o Led amarelo.
  }
  if (digitalRead(A2) == 0) { //Essa condição acessa a remoção da estrutura.
    digitalWrite(8, HIGH); //setando o pino 8 como alto para acender o Led azul.
    Serial.println("Digite um ID a ser removido: ");
    delay(5000);
    idBusca = Serial.parseInt(); //Recebendo dado da seril para a remoção.
    if (TH.Remove(idBusca) == true) { //Verifica se foi removido com sucesso.
      Serial.println("Usuário removido!");
      Serial.println();     
    }
    digitalWrite(8, LOW);//desligando o Led azul.
  }
  if (digitalRead(A0) == 0) { //Essa condição acessa a inserção da estrutura.
    digitalWrite(2, HIGH); //Setando o pino 2 como alto para acender o Led verde.
    Serial.println("Digite um ID para ser inserido: ");
    delay(5000);
    IdInsercao = Serial.parseInt();
    TH.Insere(IdInsercao, SaldoInsercao); //Chamando a função inserir da estrutura.
    Serial.println("Cadastro realizado com sucesso.");
    Serial.println();
    digitalWrite(2, LOW); //Desligando o Led verde.
  }
}
