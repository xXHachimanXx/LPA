#include <stdio.h>
#include <iostream>
#include <limits.h>

#define infinity INT_MAX

using namespace std;

class Grafo
{
private:
    int vertices;
    int arestas;
    int **matriz;
    int menorDistancia(int *distancias, bool *visitados);

public:
    ~Grafo(); //Destrutor
    Grafo();  //construtor
    Grafo(int vertices, int arestas);

    int djkstra(int inicio, int destino);
    void conectarVertices(int v1, int v2, int distancia);
    void printMatriz();
    void inicializar(); //inicializador
};

/**
 * Destrutor
 */
Grafo::~Grafo()
{
    for (int y = 0; y < vertices; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}

/**
 * Método para inicializar a matriz de adjascência.
 */
Grafo::Grafo(int vertices, int arestas)
{
    this->vertices = vertices;
    this->arestas = arestas;
    this->matriz = new int *[vertices];

    for (int y = 0; y < vertices; y++)
    {
        this->matriz[y] = new int[vertices];
    } //end for

    inicializar();
    
} //end Grafo()

/**
 * Inicializar todas as adjascências com '0'.
 */
void Grafo::inicializar()
{
    if (matriz != NULL)
    {
        for (int x = 0; x < this->vertices; x++)
            for (int y = 0; y < this->vertices; y++)
                this->matriz[x][y] = 0;
    }    
} //end init()

void Grafo::printMatriz()
{
    if (matriz != NULL)
    {
        for (int x = 0; x < this->vertices; x++)
        {
            for (int y = 0; y < this->arestas; y++)
            {
                cout << matriz[x][y] << " ";
            }
            cout << "" << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "MATRIZ NULA!";
    }
} //end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y, int distancia)
{
    this->matriz[x][y] = distancia;
    this->matriz[y][x] = distancia;
} //end conectarVertices()

/**
 * Algoritmo para encontrar o menor caminho entre dois vértices.
 */
int Grafo::djkstra(int inicio, int destino)
{
    int distancias[this->vertices];
    bool visitados[this->vertices];

    // Inicializações
    for (size_t x = 0; x < this->vertices; x++)
    {
        distancias[x] = (this->matriz[inicio][x] > 0)? this->matriz[inicio][x] : infinity;
        visitados[x] = false;
    }
    distancias[inicio] = 0;

    for (size_t x = 0; x < this->vertices-1; x++)
    {
        int menorDistancia = this->menorDistancia(distancias, visitados);
        visitados[menorDistancia] = true;

        for (size_t y = 0; y < this->vertices; y++)
        {
            if(!visitados[y] && this->matriz[menorDistancia][y] > 0 && 
                distancias[menorDistancia] + this->matriz[menorDistancia][y] < distancias[y])
            {
                distancias[y] = distancias[menorDistancia] + this->matriz[menorDistancia][y];
                this->matriz[menorDistancia][y];
                this->matriz[y][menorDistancia];
            }   
        }    
    }

    return distancias[destino-1];
}


int main()
{
    int cidades, estradas;

    while(scanf("%d %d", &cidades, &estradas) != EOF)
    {
        Grafo g(cidades, estradas);
        for (size_t x = 0; x < estradas; x++)
        {
            
        }
        
    }

    return 0;
}