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
        int kadane(int *vetor);
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
 * Algoritmo de Kadane para encontrar a maior soma
 * em um vetor 1D.
 */
int Matriz::kadane(int *vetor)
{
    int maiorTotal = -1;
    int maiorAtual = 0;
    int tamVetor = this->linhas;

    for (size_t y = 0; y < tamVetor; y++)
    {
        maiorAtual += vetor[y];
        if(maiorAtual < 0) 
            maiorAtual = 0;

        if(maiorAtual > maiorTotal)
            maiorTotal = maiorAtual;
    }

    /* ///// DEBUG /////
    cout << "Aux: ";
    for (size_t i = 0; i < tamVetor; i++)
    {
        cout << vetor[i] << " ";
    }

    cout << endl;
    */
    
    return maiorTotal;
}


/**
 * Método de força bruta (não tão eficiente)
 * para encontrar a maior soma em uma matriz.
 */
void Matriz::procurarMaiorSoma()
{   
    int maiorSoma = -1;
    int maiorAtual = 0;
    int aux[this->colunas];

    // Laço externo para definir os pontos de início de cada coluna
    // iterada no laço inteirno.
    for (size_t x = 0; x < this->colunas; x++)
    {
        // Inicializar vetor auxiliar
        for (int t = 0; t < this->colunas; t++)
            aux[t] = 0;
        
        // Laço para iterar todas as colunas a partir do ponto de início
        // pré-determinado pelo laço externo.
        for (size_t y = x; y < this->colunas; y++)
        {
            // Somar coluna atual com as colunas da direita 
            for (size_t z = 0; z < this->linhas; z++)
                aux[z] = aux[z] + this->matriz[z][y];

            // Usar algoritmo linear para trazer a maior soma
            // do vetor aux.
            maiorAtual = kadane(aux);  

            // Pegar maior soma
            maiorSoma = max(maiorAtual, maiorSoma);            
        }
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
