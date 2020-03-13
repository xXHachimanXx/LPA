#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <limits.h>

#define infinity INT_MAX

using namespace std;

class Grafo
{
    private:
        int vertices;
        int arestas;
        int **matriz;        
        int djkstra(int inicio, int destino);
        int menorDistancia(int* distancias, bool* visitados);

    public:
        ~Grafo(); //Destrutor
        Grafo();  //construtor
        Grafo(int vertices, int arestas);
        void conectarVertices(int v1, int v2, int distancia);
        void printMatriz();   
        void criarConexoes(vector<string>, int numConexoes);
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
        cout << endl;
        
    }else{ cout << "MATRIZ NULA!"; }    
}//end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int x, int y, int distancia)
{   
    this->matriz[x][y] = distancia;
    this->matriz[y][x] = distancia;
}//end conectarVertices()

/*
 * Escolher um vértice não visitado x
 * cuja distância mínima para V 0 seja a
 * menor conhecida. Se x for NULO, termine 
 * o algoritmo.
 */
int Grafo::menorDistancia(int* distancias, bool* visitados)
{
    int idMenor = -1;
    int menor = infinity;

    // Escolher um vértice não visitado x cuja distância 
    // mínima para V0 seja a menor conhecida. 
    for (size_t x = 0; x < this->vertices; x++)
    {        
        if(!visitados[x] && distancias[x] <= menor)
        {
            menor = distancias[x];
            idMenor = x;            
        }
    }
    
    return idMenor;

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

int index_of( vector<string> estacoes, string estacao)
{
    int index = -1;
    
    for(int y = 0; y < estacoes.size(); y++)
    {
        if( !(estacoes.at(y)).compare(estacao) )
        {
            index = y;
            y = estacoes.size();
        }
    }

    return index;
}

void Grafo::criarConexoes(vector<string> estacoes, int numConexoes)
{
    string estacao1;
    string estacao2;
    int index1;
    int index2;
    int distancia;

    for(int y = 0; y < numConexoes; y++)
    {
        cin >> estacao1;
        cin >> estacao2;
        cin >> distancia;

        index1 = index_of(estacoes, estacao1);
        index2 = index_of(estacoes, estacao2);
        // cout << "I1: " << index1 << " i2: " << index2 << endl;       
        // cout << "Estacao1: " << estacao1 << " Estacao2: " << estacao2 << " Distacia: " << distancia << endl;
        this->conectarVertices(index1, index2, distancia);
    }
}

int main()
{
    int numEstacoes, numConexoes;
    string nome;
    string estacaoInicial;

    cin >> numEstacoes >> numConexoes;

    while(numEstacoes != 0 && numConexoes != 0)
    {
        vector<string> estacoes = lerEstacoes(numEstacoes);        
        Grafo g(numEstacoes, numConexoes);

        g.criarConexoes(estacoes, numConexoes);
        g.printMatriz();
        
        cin >> estacaoInicial;
        cin >> numEstacoes >> numConexoes;
    }
}