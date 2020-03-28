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
    int djkstraModificado(int inicio, int destino);
    void conectarVertices(int x, int y);
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
        this->matriz[y] = new int[arestas];
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
        {
            for (int y = 0; y < this->arestas; y++)
            {
                this->matriz[x][y] = 0;
            }
            cout << endl;
        }
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
    if(distancia != 0 && distancia <= this->matriz[x][y])
    {
        this->matriz[x][y] = distancia;
    }    
    
} //end conectarVertices()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y)
{
    this->matriz[x][y] = 1;
    this->matriz[y][x] = 1;
} //end conectarVertices()

/**
 * Escolher um vértice não visitado x
 * que tenha distância mínima para o V0
 * e sendo esta a menor de todas.
 * 
 * @return Endereço da menor distância no vetor dentre os vértices não visitados.
 */
int Grafo::menorDistancia(int *distancias, bool* visitados)
{
    int indexMenor = -1;
    int menor = infinity;

    for (size_t x = 0; x < this->vertices; x++)
    {
        if( !visitados[x] && distancias[x] <= menor) 
        {
            menor = distancias[x];
            indexMenor = x;
        }
    }    
    
    return (indexMenor < 0 || menor == infinity)? -1 : indexMenor;
}

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

    for (size_t x = 0; x < this->vertices-1; x++) // -1 pois não testamos com o v0
    {
        int menorDistancia = this->menorDistancia(distancias, visitados);
        visitados[menorDistancia] = true;

        for (size_t y = 0; y < this->vertices; y++)
        {
            if(!visitados[y] && this->matriz[menorDistancia][y] > 0 && 
                distancias[menorDistancia] + this->matriz[menorDistancia][y] < distancias[y])
            {
                distancias[y] = distancias[menorDistancia] + this->matriz[menorDistancia][y];   
            }   
        }    
    }

    return distancias[destino-1];
}

/**
 * Algoritmo para encontrar o menor caminho entre dois vértices.
 */
int Grafo::djkstraModificado(int inicio, int destino)
{
    int distancias[this->vertices];
    bool visitados[this->vertices];
    int maiorCaminho = 0; // Maior caminho dentro do menor caminho    

    // Inicializações
    for (size_t x = 0; x < this->vertices; x++)
    {
        distancias[x] = (this->matriz[inicio][x] > 0)? this->matriz[inicio][x] : infinity;
        visitados[x] = false;
    }
    distancias[inicio] = 0;

    for (size_t x = 0; x < this->vertices; x++) // -1 pois não testamos com o vfinal
    {
        int idMenorDistancia = this->menorDistancia(distancias, visitados);

        if(idMenorDistancia >= 0)
        {
            visitados[idMenorDistancia] = true;

            for (size_t y = 0; y < this->vertices; y++)
            {
                // cout << "L: " << idMenorDistancia << " C: " << y << " D: " << this->matriz[idMenorDistancia][y] << endl;
                if(!visitados[y] && this->matriz[idMenorDistancia][y] > 0 && 
                    distancias[idMenorDistancia] + this->matriz[idMenorDistancia][y] < distancias[y])
                {
                    distancias[y] = distancias[idMenorDistancia] + this->matriz[idMenorDistancia][y];

                    maiorCaminho = (this->matriz[idMenorDistancia][y] > maiorCaminho) ? this->matriz[idMenorDistancia][y] : maiorCaminho;                                             
                }  
            }    
        }
        else{ x = this->vertices; maiorCaminho = -1; }
    }

    return maiorCaminho;
        
}


int main()
{
    int cidades, estradas;
    int cidadeA, cidadeB, distancia;

    cin >> cidades; cin >> estradas;

    while( !(cidades == 0 && estradas == 0) )
    {
        if ( estradas == 0 ) { cout << "IMPOSSIBLE" << endl; }
        else
        {            
            Grafo *g = new Grafo(cidades, estradas);
            // g->printMatriz();
            
            for (size_t x = 0; x < estradas; x++)
            {
                cin >> cidadeA >> cidadeB >> distancia;
                g->conectarVertices(cidadeA, cidadeB, distancia);

                // cout << "A: " << cidadeA << " B: " << cidadeB << " D: " << distancia << endl;
            }

        
            int maiorCaminho = g->djkstraModificado(0, cidades-1);

            if( maiorCaminho >= 0)
            {
                cout << maiorCaminho << endl;
            }
            else{ cout << "IMPOSSIBLE" << endl; }
                
        }        

        cin >> cidades >> estradas;       
    }
    return 0;
}
