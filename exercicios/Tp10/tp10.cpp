#include <stdio.h>
#include <iostream>

using namespace std;

class Memoria
{
public:
    int linhas, colunas;
    int **matriz;

    Memoria(int linhas, int colunas)
    {
        this->matriz = new int *[linhas];
        this->linhas = linhas;
        this->colunas = colunas;

        for (int x = 0; x < linhas; x++)
        {
            matriz[x] = new int[colunas];
        }
        inicializar();
    }

    void printMatriz() 
    {
        for (int x = 0; x < this->linhas; x++)
        {
            for (int y = 0; y < this->colunas; y++)
            {
                cout << matriz[x][y] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

private:
    void inicializar()
    {
        for (int x = 0; x < this->linhas; x++)
            for (int y = 0; y < this->colunas; y++)
                this->matriz[x][y] = -1;            
    }
};

int main()
{
    int casos = 0;
    int grana = 0;
    int modelos = 0;

    // Ler casos
    scanf("%d", &casos);

    // Casos
    for (int x = 0; x < casos; x++)
    {
        // Ler grana e roupas
        scanf("%d %d", &grana, &modelos);
        Memoria* mem = new Memoria(20, 20);
        int* stokDeCadaModelo = new int[modelos];

        // Ler roupas disponíveis
        for (int y = 0; y < modelos; y++)
        {
            // Ler quantidade de pecas disponíveis para o modelo y
            scanf("%d", &stokDeCadaModelo[y]);
            
            // Ler pecas disponíveis para o modelo y
            for (int z = 0; z < stokDeCadaModelo[y]; z++)
                scanf("%d", &mem->matriz[y][z]);
        }

        mem->printMatriz();
    }

    return 0;
}
