#include <stdio.h>
#include <iostream>

#define ull unsigned long long
#define infinity 1000000

using namespace std;
long contador = 0; // desculpa a gambiarra ;-;

/*
  #####                                                                                                                
 #     #   ####   #####   #    ##        #    #    ##     ####        ####    ####   #    #  ######  #####   #    ##   
 #        #    #  #    #  #   #  #       ##   #   #  #   #    #      #    #  #    #  ##  ##  #       #    #  #   #  #  
 #        #    #  #    #  #  #    #      # #  #  #    #  #    #      #       #    #  # ## #  #####   #    #  #  #    # 
 #        #    #  #####   #  ######      #  # #  ######  #    #      #       #    #  #    #  #       #    #  #  ###### 
 #     #  #    #  #       #  #    #      #   ##  #    #  #    #      #    #  #    #  #    #  #       #    #  #  #    # 
  #####    ####   #       #  #    #      #    #  #    #   ####        ####    ####   #    #  ######  #####   #  #    # 
*/                                                                                                                     


/**
 * Método para cortar um pedaço do vetor
 */
int merge(long* sequencia, long inicio, long meio, long fim)
{
    long tamEsq = meio - inicio + 1;
    long tamDir = fim - meio;

    long esq[tamEsq]; 
    long dir[tamDir]; 

    long x = 0, y = 0; // Variáveis para indexar topos das listas

    // Particionar vetor principal
    for (size_t p = 0; p < tamEsq; p++)
        esq[p] = sequencia[inicio+p];
    for (size_t q = 0; q < tamDir; q++)
        dir[q] = sequencia[meio + 1 + q];

    for (size_t z = inicio; z <= fim; z++)
    {
        if(x < tamEsq)
        {
            if(y < tamDir)
            {
                if(esq[x] < dir[y])
                {
                    sequencia[z] = esq[x], x++;
                }
                else
                {
                    // Swap aqui 
                    sequencia[z] = dir[y], y++, contador += tamEsq - x;
                }
            }
            else
            {
                // Distribuir o restante da esquerda para o vetor principal
                sequencia[z] = esq[x], x++;
            }
        }
        else
        {
            // Distribuir o restante da direita para o vetor principal
            sequencia[z] = dir[y], y++;
        }

    } //end for

    return 0;
}

int mergesort(long* sequencia, long inicio, long fim)
{
    // Se o problema for maior do que 1
    // eu não consigo resolver :(
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergesort(sequencia, inicio, meio);  // Ordenar primeira metade
        mergesort(sequencia, meio+1, fim);     // Ordenar segunda metade

        merge(sequencia, inicio, meio, fim); // Juntar elementos
    }

    return 0;

}

int main()
{
    long n = 0; // número de inteiros
    cin >> n;

    while (n != 0)
    {
        long* sequencia = new long[n];

        // Ler sequencia de números
        for (size_t x = 0; x < n; x++)
        {
            cin >> sequencia[x];
        }

        mergesort(sequencia, 0, n-1);        

        if (contador % 2 == 1)
            cout << "Marcelo" << endl;
        else
            cout << "Carlos" << endl;

        contador = 0; // reinicializar

        sequencia = NULL;
        cin >> n;
    }

    return 0;
}

// Se o número de permutações for ímpar(ou 0), Marcelo vence, senão, Carlos vence


/*
// Se esgotou o tamanho da lista de esquerda
        // "Pilha de cartas" está ao contrário
        if (x >= tamEsq)
        {
            sequencia[z] = dir[y], y++;
        }
        else
        {
            // Se esgotou o tamanho da lista da direita
            // "Pilha de cartas" ordenada
            if (y >= tamDir)
            {
                sequencia[z] = esq[x], x++;
            }
            else
            {
                if (esq[x] < dir[y])
                    sequencia[z] = esq[x], x++;
                else
                    sequencia[z] = dir[y], y++;
            }

        } //endif

        cout << "Sequencia: ";
        for (size_t i = 0; i < n; i++)
        {
            cout << sequencia[i] << " ";
        }
        cout << endl;
*/