#include <stdio.h>
#include <iostream>

using namespace std;

void mostraMatriz(int matriz[][])
{
    for(int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            cout << matriz[x][y] + " ";
        }

        cout << endl;
    }
}

int main()
{
    int tamanho;

    cin >> tamanho;

    int matriz[tamanho][tamanho];

    for(int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            cin >> matriz[x][y];
        }        
    }

    return 0;
}