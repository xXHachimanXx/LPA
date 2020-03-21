#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <limits.h>
#include <algorithm>

#define infinity INT_MAX

using namespace std;

class Aresta
{
public:
    int v1, v2;
    int peso;

    Aresta(int v1, int v2, int peso);
};

Aresta::Aresta(int v1, int v2, int peso)
{
    this->v1 = v1;
    this->v2 = v2;
    this->peso = peso;    
}


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
    void kruskal(vector<Aresta> arestas);
    void conectarVertices(int v1, int v2, int distancia);
    void printMatriz();
    void criarConexoes(vector<string> estacoes, int numConexoes);
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

vector<string> lerEstacoes(int estacoes)
{
    vector<string> nomes;
    string nome;
    for (int y = 0; y < estacoes; y++)
    {
        cin >> nome;
        nomes.push_back(nome);
    }

    return nomes;
}

int buscar(int *vertices, int x)
{
    while (x != vertices[x])
        x = vertices[x];

    return x;
}

bool menor(Aresta a1, Aresta a2)
{
    return (a1.peso < a2.peso);
}

void Grafo::kruskal(vector<Aresta> conexoes)
{
    int somaPesos = 0;
    int vertices[this->vertices];
    int contadorDeArestas = this->vertices - 1;

    for (size_t x = 0; x < this->vertices; x++)
    {
        vertices[x] = x;
    }

    // Ordenar arestas por peso
    sort(conexoes.begin(), conexoes.end(), menor);  


    for (size_t x = 0; x < conexoes.size(); x++)
    {
        int v1 = buscar(vertices, conexoes[x].v1);
        int v2 = buscar(vertices, conexoes[x].v2);

        if (v1 != v2)
        {
            somaPesos += conexoes[x].peso;
            vertices[v1] = v2;
            contadorDeArestas--;
        }
    }

    if (contadorDeArestas > 0)
        cout << "Impossible" << endl;
    else
        cout << somaPesos << endl;
}

int main()
{
    int numEstacoes, numConexoes;
    string nome;
    string estacaoInicial;
    string estacao1;
    string estacao2;
    vector<Aresta> conexoes;
    vector<string> estacoes;
    int index1;
    int index2;
    int distancia;

    cin >> numEstacoes >> numConexoes;

    while (numEstacoes != 0 && numConexoes != 0)
    {
        estacoes = lerEstacoes(numEstacoes);
        
        Grafo* g = new Grafo(numEstacoes, numConexoes);

        // CriarConexoes
        for (int y = 0; y < numConexoes; y++)
        {
            cin >> estacao1;
            cin >> estacao2;
            cin >> distancia;

            // ACHAR INDEX1
            for (int z = 0; z < estacoes.size(); z++)
            {
                if (!(estacoes.at(z)).compare(estacao1))
                {
                    index1 = z;
                    z = estacoes.size();
                }
            }

            // ACHAR INDEX2
            for (int z = 0; z < estacoes.size(); z++)
            {
                if (!(estacoes.at(z)).compare(estacao2))
                {
                    index2 = z;
                    z = estacoes.size();
                }
            }

            // Conectar Vértices
            g->conectarVertices(index1, index2, distancia);
            conexoes.push_back(Aresta(index1, index2, distancia));

        } // end for

        cin >> estacaoInicial;

        g->kruskal(conexoes);

        conexoes.clear();
        estacoes.clear();

        cin >> numEstacoes >> numConexoes;
    }
    return 0;
}
