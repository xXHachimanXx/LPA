#include <stdio.h>
#include <iostream>
#include <string>

#define ull unsigned long long
#define infinity 1000000

using namespace std;

ull fatorial(int tamanhoStr)
{
    if (tamanhoStr > 1)
    {
        return fatorial(tamanhoStr - 1) * tamanhoStr;
    }

    return tamanhoStr;
}

// to lowerCase e tirar 97
long quantidadeDeSubstrings(string str)
{
    long quantidade = 0;
    int numChars = 26;
    int asciiDiff = 97;
    int repeticoes[numChars];
    int tamanhoStr = str.length();
    int denominador = 1;

    // Inicializar vetor de repeticoes
    for (size_t x = 0; x < numChars; x++)
        repeticoes[x] = 0;

    // Insrir valores na "HASH"
    for (size_t x = 0; x < str.length(); x++)
    {
        repeticoes[str.at(x) - asciiDiff]++;
    }

    quantidade = fatorial(tamanhoStr);

    for (size_t y = 0; y < numChars; y++)
    {
        if (y > 0)
        {
            denominador *= fatorial(repeticoes[y]);
        }
    }

    return quantidade;
}

void printAlfa()
{
    for (size_t x = 0; x < 26; x++)
    {
        cout << (char)(x + 97) << " ";
    }

    cout << endl;
}

int main()
{
    int casos;
    string str1, str2;
    long substringsStr1 = 0, substringsStr2 = 0;

    cin >> casos;

    printAlfa();

    for (size_t x = 0; x < casos; x++)
    {
        cin >> str1 >> str2;
        substringsStr1 = quantidadeDeSubstrings(str1);
        substringsStr2 = quantidadeDeSubstrings(str2);        

        if (substringsStr1 == substringsStr2)
            cout << 's' << endl;
        else
            cout << 'n' << endl;
    }

    return 0;
}

// DEBUG
/*
for (size_t x = 0; x < numChars; x++)
{
    cout << repeticoes[x] << " ";
}
cout << endl;
*/