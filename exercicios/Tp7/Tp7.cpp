#include <stdio.h>
#include <iostream>
#include <string>

#define ull unsigned long long
#define infinity 1000000

using namespace std;

void printAlfa()
{
    for (size_t x = 0; x < 26; x++)
    {
        cout << (char)(x + 97) << " ";
    }

    cout << endl;
}

int fatorial(int tamanhoStr)
{
    if (tamanhoStr > 1)
    {
        return fatorial(tamanhoStr - 1) * tamanhoStr;
    }

    return tamanhoStr;
}

// to lowerCase e tirar 97
int permutaString(string str)
{
    int numChars = 26;
    int asciiDiff = 97;
    int repeticoes[numChars];
    int tamanhoStr = str.length();
    ull denominador = 1;
    ull quantidade = 1;

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
        if (repeticoes[y] > 1)
        {
            denominador = denominador * fatorial(repeticoes[y]);
        }
    }

    return quantidade / denominador;
}

int numSubstrings(string str)
{
    int tamString = str.length();
    ull permutacoes = str.length();

    for (size_t x = tamString; x > 1; x--)
    {
        string aux = str;
        int tamAux = aux.length();

        for (size_t y = tamAux; y > 1; y--)
        {
            // cout << "AUX: " << aux << endl;
            permutacoes += permutaString(aux);
            aux.erase((y-1), 1);
        }

        // cout << endl;
        // cout << "STR: " << str << endl;
        str.erase((x-1), 1);
    }

    return permutacoes;
}

int main()
{
    int casos;
    string str1, str2;
    long substringsStr1 = 0, substringsStr2 = 0;

    cin >> casos;

    for (size_t x = 0; x < casos; x++)
    {
        cin >> str1 >> str2;

        if (numSubstrings(str1) == numSubstrings(str2))
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