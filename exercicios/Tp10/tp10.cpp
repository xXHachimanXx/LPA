#include <stdio.h>
#include <limits.h>
#include <iostream>

#define infinito_negativo INT_MIN

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

<<<<<<< HEAD
int compras(int grana, Memoria* mem)
{
    
=======
// Globais
int granaTotal;
int numTiposDeRoupa;

int maiorCompra(int tipoDeRoupa, int grana, Memoria* custo, Memoria* memoria)
{
    int maiorValor = infinito_negativo;
    if(grana >= 0)
    {
        if(tipoDeRoupa != numTiposDeRoupa)
        {
            if(memoria->matriz[grana][tipoDeRoupa] == -1)
            {
                // Começa de 1 para não pegar a coluna com o tamanhos linha de tipos
                for (int modelo = 1; modelo <= custo->matriz[tipoDeRoupa][0]; modelo++)
                {
                    maiorValor = max(maiorValor, maiorCompra(tipoDeRoupa+1, (grana - custo->matriz[tipoDeRoupa][modelo]), custo, memoria));
                }

                memoria->matriz[grana][tipoDeRoupa] = maiorValor;
                
            }
            else{ maiorValor = memoria->matriz[grana][tipoDeRoupa]; }
        }
        else{ maiorValor = granaTotal - grana; }
    }
    return maiorValor;
>>>>>>> f5da6493f72cabf23f079b88dfb2ba7f41850183
}

int main()
{
    int casos = 0;

    // Ler numero casos
    scanf("%d", &casos);

    // Casos
    for (int x = 0; x < casos; x++)
    {
        // Ler grana e roupas
<<<<<<< HEAD
        scanf("%d %d", &grana, &modelos);

        // Como o stok dos modelos é variável então vamos alocar o máximo de memoria possivel
        Memoria* mem = new Memoria(20, 20); 
        int* stokDeCadaModelo = new int[modelos];
=======
        scanf("%d %d", &granaTotal, &numTiposDeRoupa);

        Memoria* mem = new Memoria(200, 20);
        Memoria* custo = new Memoria(20, 20);
        int numDeTipos = 0;
>>>>>>> f5da6493f72cabf23f079b88dfb2ba7f41850183

        // Ler roupas disponíveis
        for (int tipo = 0; tipo < numTiposDeRoupa; tipo++) // tipo == calça, camisa, meia...
        {
            // Ler quantidade de pecas disponíveis para o tipo y
            scanf("%d", &numDeTipos);
            custo->matriz[tipo][0] = numDeTipos; // Armazenar quantidade de modelos do tipo

            // Ler preco dos modelos disponíveis para o tipo y
            for (int modelo = 1; modelo <= numDeTipos; modelo++) // modelo == com listras, com gola...
                scanf("%d", &custo->matriz[tipo][modelo]);
        }

        int maiorValor = maiorCompra(0, granaTotal, custo, mem);
        if( maiorValor == infinito_negativo )
            printf("no solution\n");
        else
            printf("%d\n", maiorValor);
    }

    return 0;
}
