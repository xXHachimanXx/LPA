#include <stdio.h>
#include <iostream>

using namespace std;

class Matriz
{
    public: 
        int tamanho, linhas, colunas;        
        int ** matriz;

        ~Matriz(); //destrutor
        Matriz(int linhas, int colunas); //construtor   

        void lerEntradas(); 
        void mostrarMatriz();
        void procurarMaiorSoma(); 
};


/**
 * Construtor da classe Matriz.
 */
Matriz::Matriz(int linhas, int colunas)
{
    if(linhas <= 100 && colunas <= 100)
    {
        this->linhas = linhas;
        this->colunas = colunas;
        this->matriz = new int*[colunas];
        
        for(int y = 0; y < colunas; y++)
        {
            this->matriz[y] = new int[linhas];
        }//end for       

    }

}//end construtor

/**
 * Ler entradas e inicializar matriz.
 */
void Matriz::lerEntradas()
{
    for(int x = 0; x < this->linhas; x++)
    {
        for(int y = 0; y < this->colunas; y++)
        {
            cin >> this->matriz[x][y];
        }
    }
}//end lerEntradas()

/**
 * Mostrar matriz.
 */
void Matriz::mostrarMatriz()
{
    for(int x = 0; x < this->linhas; x++)
    {
        for (int y = 0; y < this->colunas; y++)
        {
            cout << this->matriz[x][y] << " ";
        }
        cout << endl;
    }
}//end mostrarMatriz()

void Matriz::procurarMaiorSoma()
{   
    int maiorSoma = this->matriz[0][0];
    int aux = maiorSoma;

    // 'x' e 'y' são os pontos de partida para os for's internos
    // com o intuito de fazê-los procurar todos os retângulos 
    // possíveis dentro da matriz
    
    for(int x = 0; x < linhas; x++)
    {
        // variável definida neste local para ser reinicializada ao término        
        // da soma de um retângulo.            
        for(int y = 0; y < colunas; y++)
        {                                                                                                                       
            // Somar elementos do retângulo interno
            cout << "RESET..." << endl;
            int aux = matriz[x][y];
            for(int z = x; z < linhas; z++)
            {
                for(int w = y; w < colunas; w++)
                {
                    aux += this->matriz[z][w]; 
                    cout << x << " " << y << " " << z << " " << w << " -> aux = " << aux << endl;
                }            
            }
            if(aux > maiorSoma){ maiorSoma = aux; }
                                    
        }            
        // Comparar soma de retângulo atual com o maior anterior                        
    }
        

    // Mostrar resultado
    cout << maiorSoma;

}//end procurarMaiorSoma()

int main()
{    
    int tamanho;
    cin >> tamanho;

    if(tamanho <= 100)
    {
        Matriz* matriz = new Matriz(tamanho, tamanho);        
        matriz->lerEntradas(); //Ler valores de entrada e inicializar matriz.
        //matriz->mostrarMatriz();
        matriz->procurarMaiorSoma(); //procurar e mostrar retângulo com maior soma
    }
    else
    {
        cout << "Erro: Tamanho inválido.";
    }

    return 0;
}//end main()
