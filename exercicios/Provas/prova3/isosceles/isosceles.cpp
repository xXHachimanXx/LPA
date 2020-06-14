#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

void clonarVetor(int v1[], int v2[], int tamanho)
{
    for(register int y = 0; y < tamanho+2; y++)    
        v2[y] = v1[y];
}

void esquerdaParaDireita(int muro[], int muroAux[], int tamanho)
{
    for (register int x = 1; x <= tamanho; x++)
        muroAux[x] = (muroAux[x - 1] < muroAux[x]) ? (muroAux[x - 1] + 1) : muroAux[x], cout << muroAux[x] << " ";			
}

void direitaParaEsquerda(int muro[], int muroAux[], int tamanho)
{    
    for (register int x = tamanho; x > 0; x--)
        muroAux[x] = (muroAux[x + 1] < muroAux[x]) ? (muroAux[x + 1] + 1) : muroAux[x], cout << muroAux[x] << " ";
}

int maiorTriangulo(int muro[], int tamanhoMuro)
{
    int maior = 0;
    int muroAux[tamanhoMuro+2];

    clonarVetor(muro, muroAux, tamanhoMuro);
	cout << "A: ";
    esquerdaParaDireita(muro, muroAux, tamanhoMuro);
	cout << endl;
	cout << "B: ";
    direitaParaEsquerda(muro, muroAux, tamanhoMuro);
	cout << endl;

    for (register int x = 0; x < tamanhoMuro; x++)    
        maior = max(muroAux[x], maior);
    
    return maior;
}

int main()
{
    int colunas = 0;
    scanf("%d", &colunas);

    int muro[colunas + 2]; // +2 para caber um 0 à esquerda e um à direita do muro
    muro[0] = 0;           // 0 a esquerda do muro
    muro[colunas + 1] = 0; // 0 a direita do muro

    // popular muro
    for (int x = 1; x < colunas; x++)
        scanf("%d", &muro[x]);

    cout << maiorTriangulo(muro, colunas) << endl;
    return 0;
}
