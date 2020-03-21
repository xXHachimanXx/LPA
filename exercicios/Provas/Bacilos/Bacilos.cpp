#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

// Variável global sim. Pode ir la e denunciar.
unsigned long long fibo[1501];

void gerarFibonacci()
{
    unsigned long long x = 1, y = 1, temp = 0;    
    fibo[0] = 0; 
    fibo[1] = 1; 
    fibo[2] = 1;

    // período de 1500
    for (size_t z = 3; z <= 1501; z++)
    {
        temp = (x + y)%1000, fibo[z] = temp, x = y, y = temp;
    }
}

int toInt(char c)
{
    return c - '0';
}

int main()
{    
    long testes; 
    char tempo[1000000];
    long long resposta, numDigitosTempo, index = 0;

    cin >> testes;
    gerarFibonacci(); // Gambiarra 9818773628% eficiente

    for (size_t x = 0; x < testes; x++)
    {        
        scanf("%s", tempo);
        numDigitosTempo = strlen(tempo);        

        if(numDigitosTempo == 1)
        {
            index = toInt(tempo[0]);
        }
        else
        {        
            index = toInt(tempo[0]) * 10 + toInt(tempo[1]);

            for (size_t y = 1; y < numDigitosTempo - 1; y++) 
            {
                index = (index * 10) % 1500 + toInt(tempo[y+1]);
            }
        }
        resposta = fibo[index];
        printf("%03lld\n", resposta);
    }    

    return 0;
}
