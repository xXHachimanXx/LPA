#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

class Grafo
{
    private:
        int vertices;
        int arestas;
        int **matriz;
        int coomponentes;

    public:
        ~Grafo(); //destrutor
        Grafo(int vertices, int arestas); //construtor
        void inicializar(); //inicializador

        void conectarVertices(int v1, int v2);
        void printMatriz();   
        int maiorComponente();
        int buscaEmProfundidade(int y, bool visitados[]);

};

/**
 * Método para inicializar a matriz de adjascência.
 */
Grafo::Grafo(int vertices, int arestas)
{
    this->vertices = vertices;
    this->arestas = arestas;
    this->matriz = new int*[vertices];

    for(int y = 0; y < vertices; y++)
    {
        this->matriz[y] = new int[vertices];
    }//end for        

    inicializar();    
}//end Grafo()

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
            cout << "\n" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }    
}//end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y)
{
    if(x < y){ matriz[x-1][y-1] = 1; }
    else{ matriz[y-1][x-1] = 1; }
    
}//end conectarVertices()

int buscaEmProfundidade()
{

}

int Grafo::maiorComponente()
{
    int maior = 0;
    bool *visitados = new bool[this->vertices]; // Vetor verificador de visitas a vertices

    // Inicializando vetor de visitados como false
    for (size_t y = 0; y < this->vertices; y++) visitados[y] = false;
        
    for (size_t y = 0; y < this->vertices; y++)
    {
        if(!visitados[y])
        {
            maior = buscaEmProfundidade(y, visitados);
        }
    }

    
    return maior;
}


/**
 * Método para verificar maior grupo de pessoas na cidade.
 */
void verificarMaiorGrupo(int habitantes, int pares)
{
    Grafo* grafo = new Grafo(habitantes, pares);

    for (size_t i = 0; i < pares; i++)
    {
        int x = 0, y = 0;

        cin >> x;
        cin >> y;

        grafo->conectarVertices(x, y);
    }

    cout << grafo->maiorComponente() << endl;
    
}

int main()
{
    int casos;
    int habitantes;
    int pares;

    cin >> casos;

    while ( casos != 0 )
    {           
        cin >> habitantes;
        cin >> pares;

        verificarMaiorGrupo(habitantes, pares);

        casos--;
    }
    
    return 0;
}