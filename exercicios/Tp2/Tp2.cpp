#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

string removerEspacos(string str)
{
    string newstr = "";


    for(int x = 0; x < str.length(); x++)
    {
        if( !isspace(str.at(x)) ) 
        {
            newstr += str.at(x);
        }
        else
        {
            x = str.length();
            newstr = newstr + " " + removerEspacos(str);
        }
    }

    cout << "NEW: " << newstr << endl;
    return newstr; 
}

void alinhar(string maiorString, string stringTotal)
{
    string novaString = "";

    

}

void justificar(int linhas)
{
    string maiorString = "";
    string stringTotal = "";

    for (int i = 0; i <= linhas; i++)
    {            
        string str = "";
        getline(cin, str);
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

    while ( linhas != 0)
    {
        justificar(linhas);

        cin >> linhas;
    }
    
    return 0;
}
