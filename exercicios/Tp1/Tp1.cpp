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


/**
 * Método de força bruta (não tão eficiente)
 * para encontrar a maior soma em uma matriz.
 */
void Matriz::procurarMaiorSoma()
{   
    int maiorSoma = 0;
    int aux = maiorSoma;

    // 'x' e 'y' são os endereços dos pontos de partida de cada variável
    // para a realização das iterações abaixo
    for(int x = 0; x < linhas; x++)
    {
        for(int y = 0; y < colunas; y++)
        {
            // 'p' e 'q' são os limites de pulos (elemento a elemento) para 
            // a realização da soma. Estes delimitam todos os retângulos
            // possíveis.
            for(int p = linhas; p > 0; p--)
            {
                for(int q = colunas; q > 0; q--)
                {        
                    // 'w' e 'z' realizam a soma do retângulo delimitado por 'p' e 'q' 
                    // partindo das coordenadas iniciais 'x' e 'y'
                    for(int z = x; z <= linhas-p; z++)
                    {
                        for(int w = y; w <= colunas-q; w++)
                        {
                            aux += this->matriz[z][w];
                            //cout << x << " " << y << " " << z << " " << w << " -> aux = " << aux << endl;
                        }
                    }

                    if(aux > maiorSoma){ maiorSoma = aux; }
                    //cout << "RESET..." << endl;
                    aux = 0;

                }//end for
            }//end for
        }//end for
    }//end for
        

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
