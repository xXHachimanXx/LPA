#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

string removerEspacos(string str)
{
    string newstr = "";    
    
    for(int x = 0; x < str.length(); x++)
    {
        if( str[x] != ' ' || (str[x] == ' ' && str[x+1] != ' '))
            newstr = newstr + str.at(x);
    }

    // Se o último caractere for um espaço em branco, remova.
    if(newstr[newstr.length()-1] == ' '){ newstr.erase(newstr.length()-1, 1); }

    return newstr; 
}

void inserirEspacos(string str, int tam)
{
    string newString = "";
    for( int x = 0; x < tam; x++ )
    {
        newString = " " + newString; // ERRO
        //cout << "LINHA: " << newString << endl;
    }
    newString += str;

    cout << newString << endl;
}

void alinhar(string maiorString, string stringTotal)
{
    string novaString = "";
    int tamMaiorString = maiorString.length();    

    for( int x = 0; x < stringTotal.length(); x++) 
    {
        if( stringTotal.at(x) != '\n' && stringTotal.at(x) != '\0' )
            novaString = novaString + stringTotal.at(x);
        else
        {
            if(!novaString.empty())
            {
                //cout << novaString << endl;
                inserirEspacos(novaString, (tamMaiorString - novaString.length()));
                novaString = "";
            }
        }            
    }

}

void justificar(int linhas)
{
    string maiorString = "";
    string stringTotal = "";    

    for (int i = 0; i <= linhas; i++)
    {
        string str = "";
        getline(cin, str);


        if(str.compare(""))
            str = removerEspacos(str);

        stringTotal = stringTotal + str;
        stringTotal = stringTotal + "\n"; // concatenar todas as strings

        if(str.length() > maiorString.length())
            maiorString = str;
    }

    alinhar(maiorString, stringTotal);
}


int main()
{
    int linhas = -1;
    
    cin >> linhas;

    while ( linhas != 0 )
    {        
        justificar(linhas);
        
        cin >> linhas;
    }
    
    return 0;
}
