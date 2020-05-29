#include <stdio.h>
#include <iostream>
#include <string.h>
#include <limits.h>

#define maxsize 1000000

using namespace std;

int minimoDeBlocos(int tiposDisponiveis[], int quantidadeDeTipos, int comprimentoDesejado)
{
    int cost[comprimentoDesejado];
    int quantidade = 0;
    cost[0] = 0;

    for (int x = 1; x < comprimentoDesejado + 1; x++)
        cost[x] = maxsize;

    for (int x = 0; x < quantidadeDeTipos; x++)
        for (int y = 0; y <= comprimentoDesejado; y++)
            cost[y] = min(cost[y], cost[y - tiposDisponiveis[x]] + 1);

    return cost[comprimentoDesejado];
}

int main()
{
    int casos = 0;
    int quantidadeDeTipos = 0;
    int comprimentoDesejado = 0;

    scanf("%d", &casos);

    for (int x = 0; x < casos; x++)
    {
        scanf("%d %d", &quantidadeDeTipos, &comprimentoDesejado);
        int tiposDisponiveis[quantidadeDeTipos];
        for (int y = 0; y < quantidadeDeTipos; y++)
            scanf("%d", &tiposDisponiveis[y]);

        printf("%d \n", minimoDeBlocos(tiposDisponiveis, quantidadeDeTipos, comprimentoDesejado));
    }

    return 0;
}