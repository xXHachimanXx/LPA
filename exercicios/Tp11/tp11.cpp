#include <stdio.h>
#include <iostream>

using namespace std;

int pegarMenor(string expressao)
{
    int menor = 0;

    for (int x = 0; x < expressao.length(); x++)
    {
        if(expressao[x] == '*')
        {
            expressao[x-1] = NULL; 
            expressao[x+1] = NULL;
            expressao[x] = atoi("" + expressao[x-1]) * atoi("" + expressao[x+1]);;
        }        
    }

    for (int x = 0; x < expressao.length(); x++)
    {
        if(expressao[x] == '+')
        {
            menor += atoi("" + expressao[x-1]) + atoi("" + expressao[x+1]);
        }        
    }
    
}


int pegarMaior(string expressao)
{

}

int main()
{
    int casos = 0;    

    // Ler casos
    scanf("%d", &casos);

    // Casos
    for (int x = 0; x < casos; x++)
    {
        string expressão;
        cin >> expressão;

        int menor = 0, maior = -1;

        menor = pegarMenor(expressao);
        maior = pegarMaior(expressao);
        
    }

    return 0;
}