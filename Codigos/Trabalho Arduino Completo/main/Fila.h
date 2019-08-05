/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Aqui nesta parte do MakeFile não tem tratamento específico de Arquivos.
 * Basicamente aqui é onde fica o cabeçalho da classe fila.
 */
#ifndef FILA_H //Usado no MajeFile para linkar o cabeçalho com o resto do corpo da classe.
#define FILA_H
#include "nohFila.h" //Incluindo o noh que será usado na fila, parte do MakeFile.
#include "SdFat.h" //Usado para manipulação do módulo SD.

class Fila {
    friend class tabelaHash;
  private:
    nohFila* PrimeiroFila ;
    nohFila* UltimoFila;
  public:
    Fila();
    ~Fila();
    void InsereFila();
    void PercorreFila();
    bool VerificaReajuste(long Saldo);
};

#endif // FILA_H
