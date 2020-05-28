#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <string.h>

#define infinity 1000000

using namespace std;
int resp = infinity;

class Grafo
{
public:
    int vertices;
    int arestas;
    int **matriz;
    int menorDistancia(int *distancias, bool *visitados);
    int tamanhoDM;
    Grafo *menoresCaminhos;
    int *pais;
    int *dist;

public:
    ~Grafo(); //Destrutor
    Grafo();  //construtor
    Grafo(int vertices, int arestas);
    Grafo *clone();
    int buscaEmProfundidade(int inicio, int v, bool visitados[], int tamanhoComponente, int tamanhoDM);
    bool buscaEmProfundidade(int ocupados[], int v, bool visitados[]);

    void conectarVertices(int v1, int v2, int distancia);
    void conectarVertices(int v1, int v2);
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
    this->pais = new int[vertices + 1];
    this->dist = new int[vertices + 1];

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
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "MATRIZ NULA!";
    }
} //end printMatriz()

/**
 * Método para clonar um grafo.
 */
Grafo *Grafo::clone()
{
    Grafo *g = new Grafo(this->vertices, this->vertices);

    for (int x = 0; x < vertices; x++)
    {
        for (int y = 0; y < vertices; y++)
        {
            g->matriz[x][y] = this->matriz[x][y];
        }
    }

    return g;
}

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y, int distancia)
{
    this->matriz[x][y] = distancia;
    this->matriz[y][x] = distancia;
}

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y)
{
    if (x != y)
        this->matriz[x][y] = 1, this->matriz[y][x] = 1;
}

/**
 * Busca em Profundidade com contagem de vértices no componente.
 * OBS.: Começa sempre em 1 pois esta função não conta a primeira visita.
 */
int Grafo::buscaEmProfundidade(int inicio, int v, bool visitados[], int tamanhoCiclo, int tamanhoDM)
{
    visitados[v] = true;

    for (size_t y = 0; y < this->vertices; y++)
    {
        if (pais[v] == y || y == v || this->matriz[v][y] <= 0) // Se não foi visitado e tem aresta faça
        {
            continue;
        }

        if (!visitados[y])
        {
            pais[y] = v;
            dist[y] = dist[v] + this->matriz[v][y];
            buscaEmProfundidade(inicio, y, visitados, tamanhoCiclo, tamanhoDM);
        }

        // A ideia no seguinte 'if' é saber se a minhoca cabe no ciclo, então
        // fazemos dist[v] + this->matriz[v][y] - dist[y] para pegar o tamanho
        // dele e comparamos com o tamanho da minhoca.
        int tamanhoCiclo = dist[v] + this->matriz[v][y] - dist[y];

        if (visitados[y] && dist[v] + this->matriz[v][y] - dist[y] >= tamanhoDM)
        {
            // Como já temos o tamanho do ciclo que cabe a minhoca, então, basta
            // calcular a menor rota de ida e volta do ciclo ( 2 * menoresCaminhos->matriz[y][inicio] )
            // e somar com o tamanho do ciclo
            resp = min(resp, tamanhoCiclo + (2 * menoresCaminhos->matriz[y][inicio]));
        }

    } // end for

    return tamanhoCiclo;
}

bool Grafo::buscaEmProfundidade(int ocupados[], int v, bool visitados[])
{
    bool resp = false;

    for (size_t y = 0; y < this->vertices; y++)
    {
        if (!visitados[y])
        {
            visitados[y] = true;
            if (ocupados[y] < 0 || buscaEmProfundidade(ocupados, ocupados[y], visitados))
                resp = true, y = this->vertices, ocupados[y] = 1;
        }

    } // end for

    return resp;
}

int maximoDeTorres(Grafo &g)
{
    int maxTorres = 0;
    bool visitados[g.vertices];
    int ocupados[g.vertices];
    memset(ocupados, -1, g.vertices);

    for (int x = 0; x < g.vertices; x++)
    {
        memset(visitados, false, g.vertices);
        maxTorres = g.buscaEmProfundidade(ocupados, x, visitados) ? maxTorres + 1 : maxTorres;
    }

    return maxTorres;
}

int main()
{
    int dimensao = 0;
    char quadrado = '.';
    int torres = 0;

    while (scanf("%d", &dimensao) != EOF)
    {
        Grafo g(dimensao, dimensao);

        for (int x = 0; x < dimensao; x++)
        {
            for (int y = 0; y < dimensao; y++)
            {
                scanf("%c", &quadrado);
                if (quadrado == '.')
                    g.conectarVertices(x, y);
            }
        }

        torres = maximoDeTorres(g);

        cout << torres << endl;
    }
    return 0;
}