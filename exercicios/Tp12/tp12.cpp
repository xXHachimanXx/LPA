#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Jogo
{
public:
	char **tabuleiro;
	int dimensao;
	Jogo();
	Jogo(int dimensao);
	~Jogo();

	friend ostream &operator<<(ostream &out, const Jogo &jogo);
	friend istream &operator>>(istream &in, Jogo &jogo);

	int getDimensao();
	char **getTabuleiro();
};

Jogo::Jogo() : Jogo(0) {}

Jogo::Jogo(int dimensao)
{
	this->dimensao = dimensao;
	this->tabuleiro = new char *[dimensao];

	for (int x = 0; x < this->dimensao; x++)
		tabuleiro[x] = new char[this->dimensao];

	for (int x = 0; x < this->dimensao; x++)
		for (int y = 0; y < this->dimensao; y++)
			this->tabuleiro[x][y] = 0;
}

Jogo::~Jogo()
{
	for (int x = 0; x < this->dimensao; x++)
		delete[] tabuleiro[x];
	delete[] tabuleiro;
}

int Jogo::getDimensao() { return this->dimensao; }

istream &operator>>(istream &in, Jogo &jogo)
{
	char celula;
	for (int x = 0; x < jogo.dimensao; x++)
		for (int y = 0; y < jogo.dimensao; y++)
		{
			in >> jogo.tabuleiro[x][y];
		}

	return in;
}

ostream &operator<<(ostream &out, const Jogo &jogo)
{
	int dimensoes = jogo.dimensao;
	for (int x = 0; x < dimensoes; x++)
	{
		for (int y = 0; y < dimensoes; y++)
		{
			out << jogo.tabuleiro[x][y];
		}
		out << endl;
	}
	return out;
}

int numeroDeTorres(Jogo &xadrez)
{
	int torres = 0;
	int dimensao_tabuleiro = xadrez.dimensao;
	char **tabuleiro = xadrez.tabuleiro;
	int contador = 0;
	bool turn = true;

	for (int x = 0; x < dimensao_tabuleiro; x++)
	{
		for (int y = 0; y < dimensao_tabuleiro; y++)
		{
			if (tabuleiro[x][y] == 'X')
			{
				for(int z = 0; z < dimensao_tabuleiro; z++)
					tabuleiro[x][y] = tabuleiro[y][x] = 'T';

				if(y+1 < dimensao_tabuleiro && tabuleiro[x][y+1] == '.')
					turn = true;
			}
			else
			{
				if (turn) contador++; 
				turn = false;
			}
		}
		turn = true;
	}

	return contador;
}

int main()
{
	int dimensao = 0;
	while (scanf("%d", &dimensao) != EOF)
	{
		Jogo &&xadrez = Jogo(dimensao);
		cin >> xadrez;
		cout << numeroDeTorres(xadrez) << endl;
	}
	return 0;
}
