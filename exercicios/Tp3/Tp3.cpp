#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

void verificarMaiorGrupo(int habitantes, int pares)
{
    
}

int main()
{
    int casos;
    int habitantes;
    int pares;

    cin >> casos;

    while ( casos != 0 )
    {           
        cin >> habitantes;
        cin >> pares;

        verificarMaiorGrupo(habitantes, pares);

        casos--;
    }
    
    return 0;
}