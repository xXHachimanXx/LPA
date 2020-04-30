#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Cálculo de MDC utilizando o algoritmo de Euclides.
 * SZ vlw dnv Flaviana sua linda SZ!!!
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

int main()
{
    int f1, f2, casos; 

    cin >> casos;

    for(int x = 0; x < casos; x++)
    {
        cin >> f1 >> f2; // entradas

        cout << mdc(f1, f2) << endl;
    }

    

    return 0;
}
/**
 * O número de cartas que cada pilha irá conter será
 * exatamente o mdc da quantidade de cartas de ambos.
 */