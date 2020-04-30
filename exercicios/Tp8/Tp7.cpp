#include <stdio.h>
#include <iostream>
#include <string>

#define ull unsigned long long
#define infinity 1000000

using namespace std;

int mergesort(int *sequencia)
{
    int iteracoes = 0;

    return 0;
}

int main()
{
    int n = 0; // número de inteiros    

    while (scanf("%d", &n) != EOF)
    {
        int sequencia[n];
        int iteracoes = 0;        
        
        if(n == 0) 
        {
            cout << "Marcelo" << endl;
            continue;
        }

        // Ler sequencia de números
        for (int x = 0; x < n; x++)
        {
            cin >> sequencia[x];        
        }

        iteracoes = mergesort(sequencia);

        if(iteracoes%2)
            cout << "Marcelo" << endl;
        else
            cout << "Carlos" << endl;
        
    }
    
    return 0;
}

// Se o número de permutações for par, Marcelo vence, senão, Carlos vence
