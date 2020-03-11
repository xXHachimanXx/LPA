#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Grafo
{
    private:
        int vertices;
        int arestas;
        int **matriz;

    public:
        ~Grafo(); //Destrutor
        Grafo();  //construtor
        Grafo(int vertices, int arestas);
        void conectarVertices(int v1, int v2);
        void printMatriz();   

    private:
        void inicializar(); //inicializador
};

/**
 * Destrutor
 */
Grafo::~Grafo()
{
    for(int y = 0; y < vertices; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}

/**
 * Inicializar todas as adjascências com '0'.
 */
void Grafo::inicializar()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
            for(int y = 0; y < this->vertices; y++)
                this->matriz[x][y] = 0;
    }
}//end init()

void Grafo::printMatriz()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
        {
            for(int y = 0; y < this->vertices; y++)
            {
                cout << matriz[x][y] << " ";
            }            
            cout << "" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }    
}//end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y)
{      
    x--; y--;
    
    matriz[x][y] = 1;
    matriz[y][x] = 1;
}//end conectarVertices()

vector<string> lerEstacoes(int estacoes)
{
    vector<string> nomes;
    string nome;
    for(int y = 0; y < estacoes; y++)
    {
        cin >> nome;
        nomes.push_back(nome);
    }

    return nomes;
}

int indexof( vector<string> estacoes, string estacao)
{
    int index = -1;
    
    for(int y = 0; y < estacoes.size(); y++)
    {
        if(estacoes.at(y).equals(estacao))
        {
            index = y;
            y = estacoes.size();
        }
    }

    return index;
}

int main()
{
    int estacoes, conexoes;
    string nome;

    cin >> numEstacoes >> numConexoes;

    while(estacoes != 0 && conexoes != 0)
    {
        vector<string> estacoes = lerEstacoes(numEstacoes);        
        
        cin >> numEstacoes >> numConexoes;
    }

}