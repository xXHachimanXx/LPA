#include <stdio.h>
#include <iostream>
#include <limits.h>

#define infinity 1000000

using namespace std;
int cu = infinity;
int inicioCiclo = -1;

class Grafo
{
public:
    int vertices;
    int arestas;
    int **matriz;
    int menorDistancia(int *distancias, bool *visitados);
    int tamanhoDM;
    Grafo* menoresCaminhos;
    int *pais;
    int *dist;


public:
    ~Grafo(); //Destrutor
    Grafo();  //construtor
    Grafo(int vertices, int arestas);
    Grafo* clone();
    Grafo* floydW();
    int buscaEmProfundidade(int inicio, int v, bool visitados[], int tamanhoComponente, int tamanhoDM);    

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
        }
    }    

    this->pais = new int[vertices+1];
    this->dist = new int[vertices+1];
    for (size_t x = 0; x < this->vertices; x++)
    {
        this->pais[x] = 0;
        this->dist[x] = 0;
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
Grafo* Grafo::clone()
{
    Grafo* g = new Grafo(this->vertices, this->vertices);

    for(int x = 0; x < vertices; x++)
    {
        for(int y = 0; y < vertices; y++)
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

Grafo* Grafo::floydW()
{
    Grafo* g2 = new Grafo(this->vertices, this->vertices);

    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = 0; y < this->vertices; y++)
        {
            if(x == y){ g2->matriz[x][y] = 0; }
            else
            {
                if( this->matriz[x][y] > 0 )
                    g2->matriz[x][y] = this->matriz[x][y];
                else
                    g2->matriz[x][y] = infinity;
            }
        }        
    }
    
    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = 0; y < this->vertices; y++)
        {
            for (size_t z = 0; z < this->vertices; z++)
            {
                g2->matriz[y][z] = min(g2->matriz[y][z], g2->matriz[y][x] + g2->matriz[x][z]);                
            }
        }        
    }

    this->menoresCaminhos = g2;

    return g2;
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
        if (y != inicioCiclo && pais[v] != y && y != inicio)
        {
            if(!visitados[y] && this->matriz[v][y] > 0)
            {
                pais[y] = v;
                // dist[y] = dist[v] + this->matriz[v][y];
                tamanhoCiclo = tamanhoCiclo + this->matriz[v][y];
                buscaEmProfundidade(inicio, y, visitados, tamanhoCiclo, tamanhoDM);
            }
            else
            {        
                inicioCiclo = y;     
                cout << "inicioCiclo = " << inicioCiclo << endl;
                // cout << "Bucetaaaa = " << tamanhoCiclo + this->matriz[v][y] << endl;            
                if(  tamanhoCiclo + this->matriz[v][y] > tamanhoDM)
                {
                    cout << " v: " << v << " y: " << y << " pais[v] = " << pais[v] << " Menor: " << tamanhoCiclo + this->matriz[v][y] + menoresCaminhos->matriz[y][inicio] << endl;
                    cu = min(cu, tamanhoCiclo + this->matriz[v][y] + menoresCaminhos->matriz[inicioCiclo][inicio]);                                    
                }
            }
        }
    }// end for
    
    return tamanhoCiclo;
}

int caminhoDaMinhoca( int salaoDM, int tamanhoDM, Grafo* g )
{
    int menor = -1;
    bool *visitados = new bool[g->vertices]; // Vetor verificador de visitas a vertices

    // Inicializando vetor de visitados como false
    for (size_t y = 0; y < g->vertices; y++)
    {
        visitados[y] = false;
        g->pais[y] = 0;
    }
    g->pais[g->vertices] = 0;

    menor = g->buscaEmProfundidade(salaoDM, salaoDM, visitados, 0, tamanhoDM);

    return menor;
}

int main()
{
    int saloes, tuneis;
    int sA, sB, tamanho;    
    int consultas;
    int salaoDM; // -> salao que a dona minhoca quer começar
    int tamanhoDM; // -> salao que a dona minhoca quer começar

    while(scanf("%d %d", &saloes, &tuneis) != EOF)
    {
        Grafo* g = new Grafo(saloes, tuneis);

        // Conectar grafo
        for (size_t x = 0; x < tuneis; x++)
        {
            cin >> sA; cin >> sB; cin >> tamanho;            
            g->conectarVertices(sA-1, sB-1, tamanho);
        }

        g->floydW(); // Gerar matriz de menores caminhos        

        // Fazer consultas
        cin >> consultas;
        for (size_t y = 0; y < consultas; y++)
        {
            cin >> salaoDM; cin >> tamanhoDM;
            caminhoDaMinhoca(salaoDM-1, tamanhoDM, g);
            cout <<  cu << endl;
            cu = infinity;
            inicioCiclo = -1;
        }    
    }

    return 0;
}
