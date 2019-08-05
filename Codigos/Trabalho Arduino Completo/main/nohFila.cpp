/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 */

#include "nohFila.h" //Aqui incluimos o cabeçalho da classe noh presente na Fila.
#define NULL 0 //Aqui definimos o arduino a variável NULL como zero.

nohFila::nohFila(long SaldoF) { // Construtor do noh da Fila.
  AnteriorFila = NULL; //Ponteiro para o anterior.
  SaldoFila = SaldoF;
}
