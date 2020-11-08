# Padrão de Projeto | Manual de Boas Práticas

## Variáveis
### No main():
> Toda declaração DEVE ser feita no topo e separada por ao menos 1 enter do resto do código
```C
#include <stdio.h>
#include <stdlib.h>

int main() {
    int inteiro;
    
    printf("Digite um numero inteiro: ");
    scanf("%i", &inteiro);
    printf("Início do programa\n%i\nFim", inteiro);
    return 0;
}
```
### Outras funções:
> Toda declaração DEVE ser feita logo abaixo a DOCSTRING e separada por ao menos 1 enter do resto do código
```C
#include <stdio.h>
#include <stdlib.h>

int somar() {
    /*Esta função retorna a soma de a e b.
    :param a: recebe um número para somar.
    :param b: recebe outro número para somar.
    :return: retorna a soma*/
    int a, int b;
    
    printf("Digite um numero inteiro: ");
    scanf("%i", &a);
    printf("Digite um numero inteiro: ");
    scanf("%i", &b);
    return a*b;
}
```



## Funções

> Toda função necessitará de uma DOCSTRING, use comentários para isso.

Descreva parâmetros com `:param nome_do_parâmetro: descrição`

Descreva retornos com `:return: descrição`
```C
int multiplicar(int a, int b){
    /*Esta função retorna a multiplicação de a e b.
    :param a: recebe um número para multiplicar.
    :param b: recebe outro número para multiplicar.*/
    return a*b;
}
```

## Menus

> Dentro de switch-cases!

## Structs

Deste jeito ele é declarado e preparado já no caminho.

```C
typedef struct{
    int func;
    float custo;
} obra;
```