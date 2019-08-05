/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Nessa parte do código fica o construtor do noh da classe tabelaHash.
 */
#include "nohHash.h" //Aqui incluimos o cabeçalho da classe, usado especialmente no MakeFile.
#define NULL 0

nohHash::nohHash(int ID, long SALDO) { //Construtor do noh da classe tabelaHash.
  //Dados do noh da classe tabelaHash.
  mProximo = NULL; //Ponteiro para o próximo noh da classe.
  mDado.ID = ID; //Armazenar o id no noh da classe.
  mDado.Saldo = SALDO; //Armazenar o saldo no noh da classe.
  mDado.Verifica = false; //Booleano para verificar se o saldo foi alterado, no caso,
  //o saldo só pode ser alterado uma vez.
}
