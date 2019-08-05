/*Identificação:
 * Trabalho de Estrutura de Dados
 * Nome do Trabalho: Banco UFLA
 * Copyright 2018/2 by Fábio Júnio Rolin, Kaio Vinícius de Morais, Otávio Augusto Resende.
 * Nessa parte do código fica o cabeçalho da classe tabelaHash, usado no MakeFile.
 */
#ifndef TABELAHASH_H //Aqui fica o link para que o MakeFile montar a classe.
#define TABELAHASH_H
#include "nohHash.h"//Chamada do cabeçalho do noh presente na tebelaHash, usando no MakeFile.
#include "Fila.h" //Inserção do cabeçalho da classe fila, usado como tipo de um dos atributos
//presente na tabelaHash.

using namespace std;

class tabelaHash { //Cabeçalho da classe tabelaHash.
    friend class Fila; //Tornando essa classe amiga da classe fila para que seje feita ope-
    //rações necessárias.
  private:
    nohHash** cadastro; //Atributo para a construção da tabelaHash.
    Fila MaioresSaldos; //Atributo para de acesso aos métodos da fila.
    int capacidade; //tamanho predefinido para a alocação da tabelaHash.
  public:
    tabelaHash(int cap); //Contrutor da tabelaHash.
    ~tabelaHash(); //Destrutor da tabelaHash.
    void Insere(int ID, long SALDO); //Método para inserir na tabela.
    void Percorre(); //Método para percorrer imprimindo a tabela.
    bool Remove(int remove); //Método para remover da tabela.
    void Busca(int ID); //Método que faz uma busca na tabela.
    void InsereNaFila(); //Método para fazer uma inserção na tabela.
};

#endif // TABELAHASH_H
