#include <iostream>
using namespace std;

class noh {
	friend class Lista;
		private:
			int dado;
			noh* proximo;
			noh* anterior;
};

class Lista {
	private:
		noh* primeiro;
		noh* ultimo;
		int nElem;
	public:
		Lista();
		~Lista() {
			for(int i = 0; i<nElem; i++) {
				RemoveIni();
			}
			primeiro = NULL;
			ultimo = NULL;
		}
		//Inserções
		bool InsereInicio(int n);
		bool InsereFim(int n);	
		bool InserePos(int n, int pos);
		//Remoções
		bool RemoveIni();
		bool RemoveFinal();
		bool RemovePos(int pos);
		//display
		void Imprime();
		void ImprimeReverse();
};

//inicializa a lista
Lista::Lista() {
	primeiro = NULL;
	ultimo = NULL;
	nElem =0;
}

bool Lista::InsereInicio(int n) {
	//aloca memória
	noh* novo = new noh;
	//testa se alocou com sucesso
	if(novo) {
		novo->dado = n;
		novo->anterior = NULL;
		if(primeiro == NULL) {
			novo->proximo  = NULL;
			primeiro = novo;
			ultimo = novo;
		}else {
			//   x   1 -> 2 -> 3
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}
		nElem++;
		return true;
	}
	return false;
}

bool Lista::InsereFim(int n) {
	//aloca memória
	noh* novo = new noh;
	//testa se alocou com sucesso
	if(novo) {
		novo->dado = n;
		novo->proximo  = NULL;
		if(primeiro == NULL) {
			novo->anterior = NULL;
			primeiro = novo;
			ultimo = novo;
		}else {
			//    1 -> 2 -> 3 -> x 
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}
		nElem++;
		return true;
	}
	return false;
}

bool Lista::InserePos(int n, int pos) {
	noh* novo = new noh;
	if((pos >= 0) and (pos < nElem) and (novo != NULL)) {
		novo->dado = n;
		if(pos == 0) {
			return InsereInicio(n);
		}else if(pos == (nElem-1)) {
			return InsereFim(n);
		}else {
			//vai até a posição
			noh* ant = NULL;
			noh* atual = primeiro;
			for(int i=0; i<pos;++i) {
				ant = atual;
				atual = atual->proximo;
			}
			//  1 <> 2 <> 3 <> 4
			ant->proximo = novo;
			novo->proximo = atual;
			atual->anterior = novo;
			novo->anterior = ant;
		}
		nElem++;
		return true;
	}
	return false;
}

bool Lista::RemoveIni() {
	if(nElem > 0) {
		// 1 -> 2 -> 3
		noh* aux = primeiro;
		primeiro = aux->proximo;
		primeiro->anterior = NULL;
		delete aux;
		nElem--;
		return true;
		
	}
	return false;
}

bool Lista::RemoveFinal() {
	if(nElem > 0) {
		//testa se só tem 1, se tiver só 1 remover no final é
		//o mesmo que remover no inicio
		if(nElem == 1) {
			return RemoveIni();
		}
		//1 -> 2 -> 3
		noh* aux = ultimo;
		ultimo->anterior->proximo = NULL;
		ultimo = aux->anterior;
		delete aux;
		nElem--;
		return true;
	}
	return false;
}

bool Lista::RemovePos(int pos) {
	if((nElem > 0) and (pos >= 0) and (pos < nElem)) {
		//checa se é o inicio
		if(pos == 0) {
			return RemoveIni();
			//checa se é o fim
		}else if(pos == (nElem-1)) {
			return RemoveFinal();
		}else {
			noh* ant = NULL;
			noh* atual = primeiro;
			for(int i=0; i<pos; i++) {
				ant = atual;
				atual = atual->proximo;
			}
			// 1 -> 2 -> r -> 4
			ant->proximo = atual->proximo;
			atual->proximo->anterior = atual->anterior;
			delete atual;
		}
		nElem--;
		return true;
	}
	return false;
}

//imprime normal
void Lista::Imprime() {
	noh* aux = primeiro;
	while(aux) {
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
}

//imprime de trás pra frente
void Lista::ImprimeReverse() {
	noh* aux = ultimo;
	while(aux) {
		cout << aux->dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}

int main()
{
	Lista li;
	li.InsereInicio(5);
	li.InsereInicio(13);
	li.InsereInicio(11);
	li.InsereInicio(9);
	li.InsereFim(100);
	li.InsereFim(90);
	li.InsereFim(80);
	li.InserePos(999,1);
	li.InserePos(888,4);
	//li.RemoveIni();
	//li.RemoveFinal();
	// li.RemovePos(2);
	// li.RemovePos(1);
	li.Imprime();
	li.ImprimeReverse();
	return 0;
}
