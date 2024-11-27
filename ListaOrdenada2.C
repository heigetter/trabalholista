// ListaOrdenada.c
#include <stdlib.h>
#include <stdio.h>

#define MAX 50
#define ERRO -1
#define bool int
#define true 1
#define false 0


typedef struct {
  int * array = (int*) malloc(MAX * sizeof(int));
  int nroElem;
} LISTA;

/* Inicialização da lista sequencial (a lista já está criada e é apontada pelo endereço em l) */
void inicializarLista(LISTA* l){
  l->nroElem = 0;
} /* inicializarLista */


/* Exibição da lista sequencial */
void exibirLista(LISTA* l){
  int i;
  printf("Lista: \" ");
  for (i=0; i < l->nroElem; i++)
    printf("%i ", l->array[i]);
  printf("\"\n");
} /* exibirLista */ 

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA* l) {
  return l->nroElem;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto nao depende do numero
   de elementos que estao sendo usados, pois a alocacao de memoria eh estatica.
   A priori, nao precisariamos do ponteiro para a lista, vamos utiliza-lo apenas
   porque teremos as mesmas funcoes para listas ligadas.   
*/
int tamanhoEmBytes(LISTA* l, int max2) {
  return sizeof(LISTA)+(sizeof(int) * max2);
} /* tamanhoEmBytes */

/* Retornar a chave do primeiro elemento da lista sequencial (caso haja) e ERRO
   caso a lista esteja vazia */
int primeiroElem(LISTA* l){
  if(l->nroElem > 0) return l->array[0];
  else return ERRO; // lista vazia
} /* primeiroElem */

/* Retornar a chave do ultimo elemento da lista sequencial (caso haja) e ERRO
   caso a lista esteja vazia */
int ultimoElem(LISTA* l) {
  if(l->nroElem > 0) return l->array[l->nroElem-1];
  else return ERRO; // lista vazia
} /* ultimoElem */

/* Retornar a chave do elemento que está na posição n da LISTA. Lembre-se que as posicoes do
   arranjo A vao de 0 a MAX-1  */
int enesimoElem(LISTA* l, int n) {
  if( (n >= 0) && (n < l->nroElem)) return l->array[n];
  else return ERRO;
} /* enesimoElem */

/* Reinicializar a estrutura */
void reinicializarLista(LISTA* l) {
  l->nroElem = 0;
} /* reinicializarLista */


/* Busca sequencial em lista ordenada ou não SEM SENTINELA */
int buscaSequencial(LISTA* l, int ch) {
  int i = 0;
  while (i < l->nroElem){
    if(ch == l->array[i]) return i; // achou
    else i++;
  }
  return ERRO; // não achou
} /* buscaSequencial */


/* Busca sequencial em lista COM SENTINELA (vetor criado com MAX+1 posições) */
int buscaSentinela(LISTA* l, int ch) {
  int i = 0;
  l->array[l->nroElem] = ch; // sentinela
  while(l->array[i] != ch) i++;
  if (i > l->nroElem -1) return ERRO; // não achou
  else return i;
} /* buscaSentinela */

/* Busca sequencial em lista COM SENTINELA (vetor criado com MAX+1 posições) 
   considerando o arranjo ordenado */
int buscaSentinelaOrdenada(LISTA* l, int ch) {
  int i = 0;
  l->array[l->nroElem] = ch; // sentinela
  while(l->array[i] < ch) i++;
  if (i == l->nroElem || l->array[i] != ch) return ERRO; // não achou
  else return i;
} /* buscaSentinela */

/* Busca binaria em lista ordenada */
int buscaBinaria(LISTA* l, int ch){
  int esq, dir, meio;
  esq = 0;
  dir = l->nroElem-1;
  while(esq <= dir) {
    meio = ((esq + dir) / 2);
    if(l->array[meio] == ch) return meio; // achou
    else {
      if(l->array[meio] < ch) esq = meio + 1;
      else dir = meio - 1;
    }
  }
  return ERRO;
} /* buscaBinaria */


/* Exclusão do elemento cuja chave seja igual a ch */
bool excluirElemLista(LISTA* l, int ch, int* max2) { 
  int pos, j;
  pos = buscaSequencial(l,ch);
  if(pos == ERRO) return false; // não existe
  for(j = pos; j < l->nroElem-1; j++) l->array[j] = l->array[j+1];
  l->nroElem--;
  if (l->nroElem < (*max2/4)){
    *max2 /= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
  }
  return true;
} /* excluirElemLista */


/* Exclusão do elemento cuja chave seja igual a ch em lista ordenada*/
bool excluirElemListaOrd(LISTA* l, int ch, int *max2) { 
  int pos, j;
  pos = buscaBinaria(l,ch);
  if(pos == ERRO) return false; // não existe
  for(j = pos; j < l->nroElem-1; j++) l->array[j] = l->array[j+1];
  l->nroElem--;
  if (l->nroElem < *max2/4){
    *max2 /= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
  }
  return true;
} /* excluirElemListaOrd */


/* Inserção em lista ordenada usando busca binária permitindo duplicação */
bool inserirElemListaOrd(LISTA* l, int reg, int* max2) { 
  if(l->nroElem >= *max2) {
    *max2 *= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
  } // lista cheia // lista cheia
  int pos = l->nroElem;
  while(pos > 0 && l->array[pos-1] > reg) {
    l->array[pos] = l->array[pos-1];
    pos--;
  }
  l->array[pos] = reg;
  l->nroElem++;
  return true;
} /* inserirElemListaOrd */



/* Inserção em lista ordenada usando busca binária sem duplicação */
bool inserirElemListaOrdSemDup(LISTA* l, int reg, int* max2) {
  if(l->nroElem >= *max2){
    *max2 *= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
  } // lista cheia
  int pos;
  pos = buscaBinaria(l,reg);
  if(pos != ERRO) return false; // elemento já existe
  pos = l->nroElem-1;
  while(pos>0 && l->array[pos]> reg) {
    l->array[pos+1] = l->array[pos];
    pos--;
  }
  l->array[pos+1] = reg;
  l->nroElem++;
  return true;
} /* inserirElemListaOrd */

int main() {
  int max2 = MAX;
  LISTA lista;
  int reg;

  // Inicializar a lista
  inicializarLista(&lista);

  // Exibir lista vazia
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista, max2));

  // Inserir elementos na lista
  reg = 50;
  inserirElemListaOrd(&lista, reg, &max2);
  reg = 35;
  inserirElemListaOrd(&lista, reg, &max2);
  reg = 14;
  inserirElemListaOrd(&lista, reg, &max2);
  reg = 32;
  inserirElemListaOrd(&lista, reg, &max2);
  reg = 30;

  // Exibir lista após inserções
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
  // Buscar um elemento na lista
  int pos = buscaSequencial(&lista, 4);
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n", pos);
  
  pos = buscaBinaria(&lista, 4);
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n", pos);
  
  pos = buscaSentinela(&lista, 4);
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n", pos);

  // Excluir alguns elementos da lista
  if (excluirElemLista(&lista, 30, &max2)) printf("Exclusao bem sucedida: 30.\n");
  if (excluirElemLista(&lista, 8, &max2)) printf("Exclusao bem sucedida: 8 (não existe na lista).\n");
  if (excluirElemLista(&lista, 14, &max2)) printf("Exclusao bem sucedida: 14.\n");

  // Exibir lista após exclusões
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista, max2));

  // Reinicializar a lista
  reinicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
  free(lista.array);
  return 0;
}
