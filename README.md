# Trabalho de Lista Dinâmica.  
## Objetivo  
Transformar uma lista originalmente estática em dinâmica.  
A primeira coisa que foi alterada foi a declaração de um array dinâmico ao inves de uma estatica.  

  
Como foi pedido na atividade quando for adicionado algum elemento quando a lista estiver no sua capicidade maxima dobrar a seu tamanho.  
Então nas funções que adicionam algum elemento foi adicionado:  
'''
if(l->nroElem >= *max2) {
    *max2 *= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
'''
E também foi pedido quando remover um elemento e a lista estiver em 25% de sua capacidade, diminuir o tamanho pela metade.  
Então nas funções que retiram algum elemento foi adicionado:  
'''
if (l->nroElem < *max2/4){
    *max2 /= 2;
    l->array = (int*) realloc(l->array, *max2 * sizeof(int));
  }
'''
