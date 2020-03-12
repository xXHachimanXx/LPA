#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Grafo
{
    private:
        int estacoes;
        int conexoes;
        int **matriz;

    public:
        ~Grafo(); //Destrutor
        Grafo();  //construtor
        Grafo(int estacoes, int conexoes);
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
    for(int y = 0; y < estacoes; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}

/**
 * Método para inicializar a matriz de adjascência.
 */
Grafo::Grafo(int estacoes, int conexoes)
{
    this->estacoes = estacoes;
    this->conexoes = conexoes;
    this->matriz = new int*[estacoes];

    for(int y = 0; y < estacoes; y++)
    {
        this->matriz[y] = new int[estacoes];
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
        for(int x = 0; x < this->estacoes; x++)
            for(int y = 0; y < this->estacoes; y++)
                this->matriz[x][y] = 0;
    }
}//end init()

void Grafo::printMatriz()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->estacoes; x++)
        {
            for(int y = 0; y < this->estacoes; y++)
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