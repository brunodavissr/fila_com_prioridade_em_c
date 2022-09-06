#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int valor;
	struct no *proximo;
}No;

typedef struct {
	No *inicio;
	No *fim;
	No *inicio_sem_prioridade;
	No *fim_sem_prioridade;
	No *inicio_prioridade;
	No *fim_prioridade;
	int tam;
}Fila;

void criar_fila(Fila *fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->inicio_sem_prioridade = NULL;
	fila->fim_sem_prioridade = NULL;
	fila->inicio_prioridade = NULL;
	fila->fim_prioridade = NULL;
	fila->tam = 0;
}

void inserir_na_fila(Fila *fila, int num) {//Aqui vamos inserir as pessoas que não têm prioridade.
	No *novo = malloc(sizeof(No));
	
	if(novo == NULL) {
		printf("\nErro ao alocar memoria\n");
		return;
	}
	novo->valor = num;
	novo->proximo = NULL;
	if(fila->tam == 0) {//Se não houver ninguém na fila. 
		fila->inicio = novo;
		fila->fim = novo;
		fila->inicio_sem_prioridade = novo;
		fila->fim_sem_prioridade = novo;
	}
	else {//Se já houver alguém na fila.
		fila->fim->proximo = novo;
		fila->fim = novo;
		fila->fim_sem_prioridade = novo;
		if(fila->inicio_sem_prioridade == NULL)//Se já tivesse pelo menos alguém na fila, mas essa(s) pessoa(s) tinha(m) prioridade, 
			fila->inicio_sem_prioridade = novo;//então a nova pessoa vai ser também o inicio da fila sem prioridade. Já que ela é a primeira sem prioridade.
	}
	fila->tam++;
}

void inserir_na_fila_com_prioridade(Fila *fila, int num) {
	No *novo = malloc(sizeof(No));
	
	if(novo == NULL) {
		printf("\nErro ao alocar memoria\n");
		return;
	}
	novo->valor = num;
	novo->proximo = fila->inicio_sem_prioridade;
	if(fila->tam == 0) {//Se não houver ninguém na fila ainda.
		fila->inicio = novo;
		fila->fim = novo;
		fila->inicio_prioridade = novo;
		fila->fim_prioridade = novo;
	}
	else {
		if(fila->fim_prioridade) {//Se já houver alguém na fila e já houver pelo menos alguém na fila de prioridade. 
			fila->fim_prioridade->proximo = novo;
			if(fila->fim == fila->fim_prioridade)
				fila->fim = novo;
			fila->fim_prioridade = novo;
		}
		else {//Se já houver alguém na fila mas não houver ninguém na fila de prioridade.
			fila->inicio = novo;
			fila->inicio_prioridade = novo;
			fila->fim_prioridade = novo;
		}
	}
	fila->tam++;
}

void remover_da_fila(Fila *fila) {
	No *remover = NULL;
	
	if(fila->tam != 0) {//Se houver alguém para remover na fila.
		remover = fila->inicio;
		if(fila->inicio_prioridade) {//Se há pelo menos alguém na fila de prioridade.
			if(fila->inicio == fila->fim) {
				fila->inicio = NULL;
				fila->fim = NULL;
				fila->inicio_prioridade = NULL;
				fila->fim_prioridade = NULL;
			}
			else {
				if(fila->inicio_prioridade == fila->fim_prioridade) {
					fila->inicio_prioridade = NULL;
					fila->fim_prioridade = NULL;
					fila->inicio = fila->inicio->proximo;
				}
				else {
					fila->inicio_prioridade = fila->inicio_prioridade->proximo;
					fila->inicio = fila->inicio->proximo;
				}
			}
		}
		else {//Se não há ninguém na fila de prioridade.
			if(fila->inicio == fila->fim) {
				fila->inicio = NULL;
				fila->fim = NULL;
				fila->inicio_sem_prioridade = NULL;
				fila->fim_sem_prioridade = NULL;
			}
			else {
				fila->inicio_sem_prioridade = fila->inicio_sem_prioridade->proximo;
				fila->inicio = fila->inicio->proximo;
			}
		}
		free(remover);
		fila->tam--;
	}
	else
		printf("\nA fila esta vazia!\n");
}

void imprimir(Fila *fila) {
	No *aux = fila->inicio;
	if(aux != NULL) {
		printf("\n[");
		while(aux->proximo) {
			printf("%i->",aux->valor);
			aux = aux->proximo;
		}
		printf("%i]\n",aux->valor);
	}
	else
		printf("\nA fila esta vazia!\n");
}

int main(void) {
	
	Fila fila;
	int opcao;
	int idade, idade_com_prioridade;
	
	criar_fila(&fila);
	
	printf("A partir de qual idade tera prioridade na fila? ");
	scanf("%i",&idade_com_prioridade);
	
	do {
		printf("\n0-Sair\n1-Inserir na Fila\n2-Remover na Fila\n3-Imprimir Fila\n4-Imprimir Inicio da Fila\n5-Imprimir Fim da Fila\n");
		printf("6-Imprimir Inicio da Fila com prioridade\n7-Imprimir Fim da Fila com prioridade\n");
		printf("\nDigite sua opcao: ");
		scanf("%i",&opcao);
		
		if(opcao == 1) {
			printf("\nDigite a idade: ");
			scanf("%i",&idade);
			
			if(idade < idade_com_prioridade)
				inserir_na_fila(&fila, idade);
			else
				inserir_na_fila_com_prioridade(&fila, idade);
		}
		else if(opcao == 2)
			remover_da_fila(&fila);
		else if(opcao == 3)
			imprimir(&fila);
		else if(opcao == 4) {
			if(fila.inicio)
				printf("\nIdade da pessoa no inicio da fila: %i\n",fila.inicio->valor);	
			else
				printf("\nA fila esta vazia!\n");
		}
		else if(opcao == 5) {
			if(fila.fim)
				printf("\nIdade da pessoa no fim da fila: %i\n",fila.fim->valor);
			else
				printf("\nA fila esta vazia!\n");
		}
		else if(opcao == 6) {
			if(fila.inicio_prioridade)
				printf("\nIdade da pessoa no inicio da fila com prioridade: %i\n",fila.inicio_prioridade->valor);
			else
				printf("\nNao ha pessoas na fila com prioridade!\n");
		}
		else if(opcao == 7) {
			if(fila.fim_prioridade)
				printf("\nIdade da pessoa no fim da fila com prioridade: %i\n",fila.fim_prioridade->valor);
			else
				printf("\nNao ha pessoas na fila com prioridade!\n");
		}
			
	}while(opcao != 0);
	
	return 0;
}
