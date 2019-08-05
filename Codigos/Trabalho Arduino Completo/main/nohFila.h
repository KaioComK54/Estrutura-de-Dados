/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Aqui está o cabeçalho do noh da fila, usado especialmente no MakeFile.
 */
#ifndef NOHFILA_H //Parte para fazer a ligação com a "nohFila.cpp", usado pelo MakeFile.
#define NOHFILA_H

class nohFila {
    friend class Fila;
  private:
    long SaldoFila; //Variável para armazenar um saldo no Noh da fila.
    nohFila* AnteriorFila; //Ponteiro para o noh anterior da fila.
  public:
    nohFila(long SaldoF);
};


#endif // NOHFILA_H
