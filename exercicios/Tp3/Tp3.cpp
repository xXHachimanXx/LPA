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

    public:
        ~Grafo(); //destrutor
        Grafo(int vertices, int arestas); //construtor

        void conectarVertices(int v1, int v2);
        void printMatriz();   
        int maiorComponente();
        int buscaEmProfundidade(int y, bool visitados[], int tamanhoComponente);

    private:
        void inicializar(); //inicializador

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


/**
 * Busca em Profundidade com contagem de vértices no componente.
 * OBS.: Começa sempre em 1 pois esta função não conta a primeira visita.
 */
int Grafo::buscaEmProfundidade(int v, bool visitados[], int tamanhoComponente)
{   
    if(!visitados[v])
    {
        visitados[v] = true;    
        tamanhoComponente++;    
    }


    for (size_t y = 0; y < this->vertices; y++)
    {
        if(!visitados[y] && this->matriz[v][y] == 1) 
        {
            tamanhoComponente = buscaEmProfundidade(y, visitados, tamanhoComponente);
        }
    }
    return tamanhoComponente;
}

int Grafo::maiorComponente()
{
    int maior = 0, temp = 0;
    bool *visitados = new bool[this->vertices]; // Vetor verificador de visitas a vertices

    // Inicializando vetor de visitados como false
    for (size_t y = 0; y < this->vertices; y++) 
        visitados[y] = false;
    
    // Rodar em todos os componentes
    for (size_t y = 0; y < this->vertices; y++)
    {               
        // A função começa com 1 pois esta não conta a primeira visita
        if(!visitados[y])
        {
            temp = buscaEmProfundidade(y, visitados, 0);             
            maior = (temp >= maior)? temp : maior;
            temp = 0;
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
        //cout << endl;
    }

    //grafo->printMatriz();
    int maior = grafo->maiorComponente();
    cout << maior << endl;    
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