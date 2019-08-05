  if(n == 0){
              noh* aux = primeiro;
              while(aux!=NULL){
                  lista3->insere(aux->dado);
                  aux = aux->proximo;
              }
              aux = primeiro;
              noh* anterior = NULL;
              while(aux!=NULL){
                  anterior = aux;
                  aux = aux->proximo;
                  delete anterior;
                  --tamanho;
              }
              primeiro = NULL;
              ultimo = NULL;
              tamanho = 0;
              lista3->ultimo->proximo = NULL;
              lista3->primeiro->anterior = NULL;
          }else if(n == tamanho-1){
              noh* aux = ultimo;
              lista3->insere(aux->dado);
              ultimo = ultimo->anterior;
              delete aux;
              ultimo->proximo = NULL;
              --tamanho;
              lista3->primeiro->anterior = NULL;
              lista3->ultimo->proximo = NULL;
          }else{
              noh* aux = primeiro;
              int i=0;
              while(i < n){
                  aux = aux->proximo;
                  ++i;
              }
              noh* anterior = aux->anterior;
              while(aux != NULL){
                  lista3->insere(aux->dado);
                  noh* aux2 = aux;
                  aux = aux->proximo;
                  delete aux2;
                  --tamanho;
              }
              anterior->proximo = NULL;
              ultimo = anterior;
              lista3->primeiro->anterior = NULL;
              lista3->ultimo->proximo = NULL;
          }
          if(tamanho == 0){
              primeiro = NULL;
              ultimo = NULL;
          }else if(tamanho == 1){
              primeiro->anterior = NULL;
              primeiro->proximo = NULL;
              ultimo = primeiro;
          }
