#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

#define ASCII__0 48

bool isANumber(char a)
{
    return (a >= '0' && a <= '9' && a != '*' && a != '+');
}

struct Somas
{
    long somasMaximas[100];
    long somasMinimas[100];
};

void inicializar(Somas* s)
{
    memset(s->somasMaximas, 0, 100);
    memset(s->somasMinimas, 0, 100);
}

void calcularSomas(string expressao)
{
    long a = 0, b = 0;
    long aux = 0;
    int tamanhoExpressao = expressao.length();
    char operacao = '*';
    struct Somas somas;
    long resp[2] = {0, 1}; // vetor de saída com os valores desejados

    inicializar(&somas);

    for (int x = 0; x <= tamanhoExpressao; x++)
    {
        if(isANumber(expressao[x]))        
            aux = aux*10 + expressao[x] - '0';
        else
        {
            if(operacao == '*')
            {
                if(b == 0) { somas.somasMinimas[b] = aux, b++; }
                else       { somas.somasMinimas[b-1] *= aux;   }
                somas.somasMaximas[a] = aux, a++;
            }
            else
            {
                if(a == 0) { somas.somasMaximas[a] = aux, b++; }
                else       { somas.somasMaximas[a-1] += aux;   }
                somas.somasMinimas[b] = aux, b++;
            }
            operacao = expressao[x], aux = 0;
        }
    }

    for (long x = 0; x < b; x++)
        resp[0] += somas.somasMinimas[x];    
    for (long x = 0; x < a; x++)
        resp[1] *= somas.somasMaximas[x];
    
    cout << "The maximum and minimum are " << resp[1] << " and " << resp[0] << '.' << endl;
}

int main()
{
    int casos = 0;

    // Ler casos
    scanf("%d", &casos);

    // Casos
    for (long x = 0; x < casos; x++)
    {
        string expressao;
        cin >> expressao;

        calcularSomas(expressao);
    }

    return 0;
}