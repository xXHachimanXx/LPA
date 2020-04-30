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
    Grafo(int vertices, int arestas)
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

    ~Grafo()
    {
        for (int y = 0; y < vertices; y++)
        {
            delete matriz[y];
        }
        delete matriz;
    }

    int getVertices() { return this->vertices; }
    int getArestas() { return this->arestas; }

    void printMatriz()
    {
        if (matriz != NULL)
        {
            for (int x = 0; x < this->vertices; x++)
            {
                for (int y = 0; y < this->vertices; y++)
                {
                    cout << matriz[x][y] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "MATRIZ NULA!";
        }
    } //end printMatriz()

    /**
     * Métodos para registrar adjascência na matriz.
     */
    void conectarVerticesMaoDupla(int x, int y)
    {
        x--;
        y--;

        matriz[x][y] = 1;
        matriz[y][x] = 1;
    } //end conectarVertices()

    void conectarVerticesMaoUnica(int x, int y)
    {
        x--;
        y--;

        matriz[x][y] = 1;
    } //end conectarVertices()

    /**
     * Busca em Profundidade com contagem de vértices no componente.
     * OBS.: Começa sempre em 1 pois esta função não conta a primeira visita.
     */
    void buscaEmProfundidade(int v, bool *visitados)
    {
        visitados[v] = true;

        for (size_t y = 0; y < this->vertices; y++)
        {
            if (!visitados[y] && this->matriz[v][y] == 1)
            {
                buscaEmProfundidade(y, visitados);
            }
        }
    }

    /**
     * Método para transpor um grafo(G^t).
     */
    void transpor()
    {
        int aux = 0;
        //o que é linha vira coluna
        for (size_t x = 0; x < this->vertices; ++x)
        {
            for (size_t y = x+1; y < this->vertices; ++y)
            {
                aux = this->matriz[x][y];
                this->matriz[x][y] = this->matriz[y][x];
                this->matriz[y][x] = aux;
            }
        }
    }

private:
    /**
     * Inicializar todas as adjascências com '0'.
     */
    void inicializar()
    {
        if (matriz != NULL)
        {            
            for (size_t x = 0; x < this->vertices; x++)
                for (size_t y = 0; y < this->vertices; y++)
                    this->matriz[x][y] = 0;
        }
    } //end init()

}; //end class Grafo

bool testarConectividade(Grafo *g)
{
    int vertices = g->getVertices();
    bool resp = true;

    // Testar com grafo original
    bool visitados[vertices];    
    memset(visitados, 0, vertices);

    g->buscaEmProfundidade(0, visitados);

    for (size_t y = 0; y < vertices; y++)
    {
        if (!visitados[y]){
            resp = 0;
            y = vertices;
        }
    }

    
    if(resp == 1)
    {
        //Testar com grafo transposto
        g->transpor();
        memset(visitados, 0, vertices);
        g->buscaEmProfundidade(0, visitados);

        for (size_t y = 0; y < vertices; y++)
        {
            if (!visitados[y]){
                resp = 0;
                y = vertices;
            }
        }
    }
    

    return resp;
}

int main()
{
    int intersec, ruas;
    int v, w, mao;
    scanf("%d %d", &intersec, &ruas);

    do
    {        
        if(ruas == 0 && intersec == 0)
        { break; }
        Grafo cidade(intersec, ruas);

        for (size_t x = 0; x < ruas; x++)
        {
            scanf("%d %d %d", &v, &w, &mao);
            if(mao == 1)
                cidade.conectarVerticesMaoUnica(v, w);
            else
                cidade.conectarVerticesMaoDupla(v, w);
        }
        
        // Testar conectividade
        printf("%d\n", testarConectividade(&cidade));        
        
    }
    while ((scanf("%d %d", &intersec, &ruas) != EOF));    

    return 0;
}
