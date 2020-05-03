#include <stdio.h>
#include <iostream>

using namespace std;

typedef long long ll;


ll maiorValorDeAlberto(int* cartoes, int quantidade) 
{
    ll somas[2][quantidade];
    
    // preencher matriz com os n-1 maiores valores
    for (int x = 0; x < quantidade; x++)
        somas[0][x] = max(cartoes[x], cartoes[x+1]);

    int vez = 0;
    int vezPassada = 1;

    for(int pedaco = 4; pedaco <= quantidade; pedaco += 2)
    {
        vezPassada = vez; vez = !vez;

        // Como Wanderley quer ferrar com a gente, ele sempre vai escolher o maior
        // número na vez dele. Então, para um pedaço de 4, nossa soma será
        // max( ponta esquerda + o segundo maior, ponta direita + segundo maior )
        for(int x = 0, y = pedaco-1; y < quantidade; x++, y++)
        {
            somas[vez][x] = max( cartoes[x] + min(somas[vezPassada][x+1], somas[vezPassada][x+2]),
                                 cartoes[y] + min(somas[vezPassada][x],   somas[vezPassada][x+1]) );
        }
    }        
    
    // Quando tivermos o maior pedaço possível, o for interno vai executar apenas uma vez
    // colocando, assim, a maior soma de Alberto no "topo".
    return somas[vez][0];
            
}

int main()
{
    int n = 0; // número de cartoes
    while (scanf("%d", &n) != EOF)
    {
        int cartoes[n]; // vetor de cartoes
        ll maiorValor = -1; // maior valor procurado

        // preencher vetor de cartoes
        for (int x = 0; x < n; x++)        
            scanf("%d", &cartoes[x]);

        maiorValor = maiorValorDeAlberto(cartoes, n);        
        cout << maiorValor << endl;
        
    }
    
    return 0;
}