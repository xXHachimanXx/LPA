#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Cálculo de MDC utilizando o algoritmo de Euclides.
 * SZ Flaviana sua linda!!!
 */
int mdc(int x, int y)
{
    int mdc = 0;
    int a = max(x, y);
    int b = min(x, y);

    while(a % b != 0)
    {
        mdc = a%b;
        // cout << mdc << endl;
        a = b;    
        b = mdc;
    }

    return (mdc == 0)? min(a, b) : mdc;
}

void numeroDeEstacas(int x, int y)
{
    int perimetro = (2*x) + (2*y);
    int numEstacas = (perimetro)/(mdc(x, y));
    cout << numEstacas << endl; 
}

int main()
{
    int x, y; // Dimensões do terreno 
    
    while (scanf("%d%d", &x, &y) != EOF)
    {
        numeroDeEstacas(x, y);
    }

    return 0;
}