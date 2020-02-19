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
    
    // cout << newstr << endl;
    return newstr; 
}

void inserirEspacos(string str, int tam)
{
    string newString = "";

    for( int x = 0; x < tam; x++ )
    {
        newString = " " + newString + str[x]; // ERRO
    }   
    
    cout << "LINHA: " << newString << endl;

}

void alinhar(string maiorString, string stringTotal)
{
    string novaString = "";
    int tamMaiorString = maiorString.length();    

    for( int x = 0; x < stringTotal.length(); x++) 
    {
        if(stringTotal.at(x) != '\n' && stringTotal.at(x) != '\0' )
            novaString = novaString + stringTotal.at(x);
        else
        {
            cout << "LINHA: " << tamMaiorString - novaString.length() << endl;
            inserirEspacos(novaString, (tamMaiorString - novaString.length()));
            novaString = "";
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

        // cout << "LINHA: " << str << endl;

        if(str.compare(""))
            str = removerEspacos(str);

        stringTotal = stringTotal + str;
        stringTotal = stringTotal + "\n"; // concatenar todas as strings

        if(str.length() > maiorString.length())
            maiorString = str;
    }
        

    //cout << maiorString << endl;

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
