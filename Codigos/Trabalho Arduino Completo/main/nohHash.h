/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Nesta parte do MakeFile, está contido o cabeçalho do noh da classe tabelaHash, incluindo,
 * uma struct que contém os dados que estarão dentro do noh, a struct tem tipos primitivos
 * diferentes.
 */
#ifndef NOHHASH_H //Aqui está o link do cabeçalho com os construtores do Noh da tabelaHash.
//Essa parte também é usada no MakeFile do código.
#define NOHHASH_H

struct Dados { //struct de dados mencionada na descrição acima.
  int ID; //Variável usada para armazenar o ID no noh da classe tabelaHash.
  long Saldo; //Variável usada para armazenar o saldo no noh da classe tabelaHash.
  bool Verifica; //Booleano usado para checar se o saldo do noh foi alterado.
};

class nohHash { //Cabeçalho do nohHash, noh presente na classe tabelaHash.
    friend class tabelaHash; //Deixando essa classe noh amiga da tabelaHash para poder
    //realizar as necessitadas operações.
  private:
    nohHash* mProximo; //Ponteiro para o próximo noh da classe.
    Dados mDado; //Variável que usa a struct presente na parte superior da descrição.
  public:
    nohHash(int ID, long SALDO);
};

#endif // NOHHASH_H
