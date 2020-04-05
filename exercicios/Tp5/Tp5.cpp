#include <stdio.h>
#include <iostream>
#include <limits.h>

#define infinity 1000000

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
    Grafo* clone();
    Grafo* transpor(); //transpor matriz do grafo

    int djkstra(int inicio, int destino);
    int djkstraModificado(int inicio, int destino);
    Grafo* floydW();
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

Grafo* Grafo::transpor()
{
    Grafo* gt = this->clone();

    //o que é linha vira coluna
    for(int x = 0; x < this->vertices; x++)
    {
        for(int y = 0; y < this->vertices; y++)
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
    if(distancia > 0)    
    {           
        if(this->matriz[x][y] == -1 && this->matriz[y][x] == -1 )
        {
            this->matriz[x][y] = distancia;
            this->matriz[y][x] = distancia;  
        }
        else
        {
            int menor = min( min(this->matriz[x][y], this->matriz[y][x]), distancia);
            this->matriz[x][y] = menor;
            this->matriz[y][x] = menor;

        }
    }
    /*
       if( this->matriz[x][y] == 0)
       {
           if(this->matriz[y][x] == 0)
           { this->matriz[x][y] = distancia; }
           else
           {
                this->matriz[y][x] = (this->matriz[y][x] > distancia)? distancia : this->matriz[y][x];
           }
       }
       else
       {
            this->matriz[x][y] = (this->matriz[x][y] > distancia) ? distancia : this->matriz[x][y];
       }

    } 
    */   
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
        if( !visitados[x] && distancias[x] <= menor ) 
        {
            menor = distancias[x];
            indexMenor = x;
        }
    }    
    
    // cout << "CUUU" << indexMenor << endl;
    return indexMenor;
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
                // CAMINHO QUE EU QUERO VAI SAIR DAQUI -> this->matriz[menorDistancia][y]
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
    int contador = 0;
    int m = -1; 
    // cout << "I: " << inicio << " D: " << destino << endl;

    // Inicializações
    for (size_t x = 0; x < this->vertices; x++)
    {
        distancias[x] = (this->matriz[inicio][x] > 0)? this->matriz[inicio][x] : infinity;
        visitados[x] = false;
    }
    distancias[inicio] = 0;
    m = distancias[inicio+1];

    for (size_t x = 0; x < this->vertices-1; x++) // -1 pois não testamos com o v0
    {
        int menorDistancia = this->menorDistancia(distancias, visitados);

        if(menorDistancia >= 0)
        {
            visitados[menorDistancia] = true;

            for (size_t y = 0; y < this->vertices; y++)
            {
                // cout << " m[" << menorDistancia << "][" << y << "] = " << this->matriz[menorDistancia][y] << endl;
                // cout << "Maqui: " << m << endl;            
                if(!visitados[y] && this->matriz[menorDistancia][y] > 0 && 
                    distancias[menorDistancia] + this->matriz[menorDistancia][y] < distancias[y])
                {
                    // CAMINHO QUE EU QUERO VAI SAIR DAQUI -> this->matriz[menorDistancia][y]
                    distancias[y] = distancias[menorDistancia] + this->matriz[menorDistancia][y];
                    m = max(this->matriz[menorDistancia][y], m);
                }        
            }
        }else{ x = this->vertices; m = -1; }
    }

    // cout << "M: " << m << endl;

    return m;
}


Grafo* Grafo::floydW()
{
    Grafo* g2 = new Grafo(this->vertices, this->vertices);

    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = 0; y < this->vertices; y++)
        {
            //g2->matriz[x][y]
            if(x == y){ g2->matriz[x][y]; }
            else
            {
                if( this->matriz[x][y] > 0 )
                    g2->matriz[x][y] = this->matriz[x][y];
                else
                    g2->matriz[x][y] = infinity;
            }
        }        
    }
    
    int m = -1;
    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = 0; y < this->vertices; y++)
        {
            for (size_t z = 0; z < this->vertices; z++)
            {
                // g2->matriz[y][z] = min(g2->matriz[y][z], g2->matriz[y][x] + g2->matriz[x][z]);
                g2->matriz[y][z] = min(g2->matriz[y][z], g2->matriz[y][x] + g2->matriz[x][z]);                
            }
        }        
    }
    //g2->printMatriz();

    return g2;    
}

int Grafo::maiorMenorCaminho()
{
    int maiorMenorCaminho = -1;
    int dm = 0;

    for (size_t x = 0; x < this->vertices; x++)
    {
        for (size_t y = x+1; y < this->vertices-1; y++)
        {
            dm = this->djkstraModificado(x, y);

            if(dm >= 0)            
                maiorMenorCaminho = max(maiorMenorCaminho, dm);
            else
                x = y = this->vertices, maiorMenorCaminho = -1;
        }        
    }
    
    return maiorMenorCaminho;
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
            Grafo *g = new Grafo(cidades, cidades);            
            Grafo *g2;

            for (size_t x = 0; x < estradas; x++)
            {
                cin >> cidadeA >> cidadeB >> distancia;
                g->conectarVertices(cidadeA, cidadeB, distancia);

                // cout << "A: " << cidadeA << " B: " << cidadeB << " D: " << distancia << endl;
            }
            
            // g->printMatriz();
            
            int maiorCaminho = g->maiorMenorCaminho();

            // cout << "A: " << maiorCaminho << " B: " << maiorCaminho2 << endl;            

            if( maiorCaminho < infinity && maiorCaminho > 0 )
            {
                cout << maiorCaminho << endl;
            }
            else{ cout << "IMPOSSIBLE" << endl; }
                
        }        
        cin >> cidades >> estradas;       
    }
    return 0;
}
