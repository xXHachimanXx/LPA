#include <stdio.h>
#include <iostream>
#include <limits.h>

#define infinity 1000000
#define infinito INT32_MAX

using namespace std;

class Grafo
{
public:
    int vertices;
    int arestas;
    int **matriz;
    int menorDistancia(int *distancias, bool *visitados);

public:
    ~Grafo(); //Destrutor
    Grafo();  //construtor
    Grafo(int vertices, int arestas);
    Grafo *clone();
    Grafo *transpor(); //transpor matriz do grafo

    int djkstra(int inicio, int destino);
    int djkstraModificado(int inicio, int destino);
    void floydW();
    void conectarVertices(int x, int y);
    void conectarVertices(int v1, int v2, int distancia);
    void printMatriz();
    void inicializar(); //inicializador
    int maiorMenorCaminho();
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
                this->matriz[x][y] = -1;
            }
        }
    }

    for (size_t x = 0; x < this->vertices; x++)
        for (size_t y = 0; y < this->vertices; y++)
            this->matriz[x][y] = infinity;

    for (size_t x = 0; x < this->vertices; x++)
        this->matriz[x][x] = 0;
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

Grafo *Grafo::transpor()
{
    Grafo *gt = this->clone();

    //o que é linha vira coluna
    for (int x = 0; x < this->vertices; x++)
    {
        for (int y = 0; y < this->vertices; y++)
        {
            gt->matriz[x][y] = this->matriz[y][x];
        }
    }

    return gt;
}

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y, int distancia)
{
    this->matriz[x][y] = distancia;
    this->matriz[y][x] = distancia;

} //end conectarVertices()

void Grafo::floydW()
{
    int m = -1;
    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = 0; y < this->vertices; y++)
        {
            for (size_t z = 0; z < this->vertices; z++)
            {
                this->matriz[y][z] = min(this->matriz[y][z], this->matriz[y][x] + this->matriz[x][z]);
            }
        }
    }
}

/**
 * Equação de recorrência: 
 * 
 *                ---> D(v, 0) + ( d(u,v) - g )*c(u) se c(v) <= c(u) && g <= d(uv)
 * D(u, g) = min -|
 *                ---> D(v, U-d(u,v)) + ( U - g )*c(u) se c(v) > c(u) 
 * Tirada de: https://dl.acm.org/doi/pdf/10.1145/1978782.1978791
 */
int menorCustoRec(Grafo *g, int **cache, int *tabelaDePrecosGas, int cidades, int cidade, int gasosa, int tanque)
{
    if (cidade == cidades - 1) // Cheguei ao destino :)
        gasosa = 0;

    int custo = cache[cidade][gasosa];
    int menorCusto = infinity;

    if (custo == -1)
    {
        for (int proximaCidade = cidade + 1; proximaCidade < cidades; proximaCidade++)
        {
            custo = infinity;
            if (g->matriz[cidade][proximaCidade] <= tanque)
            {
                if (tabelaDePrecosGas[proximaCidade] > tabelaDePrecosGas[cidade])
                {
                    custo = menorCustoRec(g, cache, tabelaDePrecosGas, cidades, proximaCidade,
                                          (tanque - g->matriz[cidade][proximaCidade]), tanque) + (tanque - gasosa) * tabelaDePrecosGas[cidade];
                }
                else
                {
                    if (gasosa >= g->matriz[cidade][proximaCidade])
                    {
                        custo = menorCustoRec(g, cache, tabelaDePrecosGas, cidades,
                                              proximaCidade,
                                              (gasosa - g->matriz[cidade][proximaCidade]), tanque);
                    }
                    else
                    {
                        custo = menorCustoRec(g, cache, tabelaDePrecosGas, cidades,
                                              proximaCidade,
                                              0, tanque) +
                                (g->matriz[cidade][proximaCidade] - gasosa) * tabelaDePrecosGas[cidade];
                    }
                }

                if(custo >= 0 && custo < menorCusto) menorCusto = custo;
                //menorCusto = custo >= 0 ? min(custo, menorCusto) : menorCusto;
            }
        } // end for
    }
    else
    {
        menorCusto = custo;
    }

    cache[cidade][gasosa] = menorCusto;

    return cache[cidade][gasosa];
}

int menorCusto(Grafo *g, int cidades, int tanque, int *tabelaDePrecosGas)
{
    // Sim, está um caquinha porém, por motivos de "Sem tempo irmão",
    // ficará assim msm ;)
    int **cache = new int *[cidades];
    for (int x = 0; x < cidades; x++)
        cache[x] = new int[tanque + 1];

    int custo = 0;
    cache[cidades - 1][0] = 0;

    custo = menorCustoRec(g, cache, tabelaDePrecosGas, cidades, 0, tanque, tanque);

    for (int y = 0; y < cidades; y++)    
        delete cache[y];    
    delete [] cache;

    return custo;
}

int main()
{
    int cidades, estradas, tanque;
    int cidadeA, cidadeB, distancia;
    int m = infinity;

    scanf("%d%d%d", &cidades, &estradas, &tanque);

    while (!(cidades == 0 && estradas == 0 && tanque == 0))
    {
        if (estradas == 0)
        {
            printf("-1\n");
        }
        else
        {
            Grafo *g = new Grafo(cidades, cidades);
            int *tabelaDePrecosGas = new int[cidades];

            // Ler estradas e conexoes
            for (size_t x = 0; x < estradas; x++)
            {
                scanf("%d%d%d", &cidadeA, &cidadeB, &distancia);
                g->conectarVertices(--cidadeA, --cidadeB, distancia);
            }

            // Ler tabela de preços
            for (size_t x = 0; x < cidades; x++)
                scanf("%d", &tabelaDePrecosGas[x]);

            g->floydW();

            if (g->matriz[0][cidades - 1] == infinity)
            {
                printf("-1\n");
            }
            else
            {
                // Se é possível chegar no final...
                int m = menorCusto(g, cidades, tanque, tabelaDePrecosGas);
                printf("%d\n", (m == infinity ? -1 : m));
            }
        }
        scanf("%d %d %d", &cidades, &estradas, &tanque);
    } // end while
    return 0;
}
