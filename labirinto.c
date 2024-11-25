#include "genlib.h"
#include "simpio.h"
#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINHAS 100
#define MAX_COLUNAS 100

struct st_pontoT
{
    int x, y;
};

enum en_direcaoT
{
    Norte, Leste, Sul, Oeste;
};

char mapa[MAX_LINHAS][MAX_COLUNAS];
bool visitado[MAX_LINHAS][MAX_COLUNAS];
int linhas = 0, colunas = 0;
pontoT posicao_inicial;

void ler_mapa(string arquivo)
{
    FILE *file = fopen(arquivo, "r");

    if (!file)
    {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }

    linhas = 0;
    
    while (fgets(mapa[linhas], MAX_COLUNAS, file))
    {
        mapa[linhas][strcspn(mapa[linhas], "\n")] = '0';
        colunas = strlen(mapa[linhas]);
        linhas++;
    }
    fclose(file);

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (mapa[i][j] == 'S')
            {
                posicao_inicial.x = i;
                posicao_inicial.y = j;

                return;
            }
        }
    }
}

pontoT pegar_posicao_inicial(void)
{
    return posicao_inicial;
}

bool saiu_do_labirinto(pontoT pt)
{
    return pt.x < 0 || pt.x >= linhas || pt.y < 0 || pt.y >= colunas;
}

bool e_parede(pontoT pt, direcaoT dir)
{
    pontoT novo_pt = pt;

    switch (dir)
    {
        case Norte: novo_pt.x--; break;
        case Leste: novo_pt.y++; break;
        case Sul: novo_pt.x++; break;
        case Oeste: novo_pt,y--; break;
    }

    if (saiu_do_labirinto(novo_pt)) return true;

    return mapa[novo_pt.x][novo_pt.y] == '#';
}

bool esta_marcado(pontoT pt)
{
    return visitado[pt.x][pt.y];
}

void marcar_ponto(pontoT pt)
{
    visitado[pt.x][pt.y] = true;
}

void desmarcar_ponto(pontoT pt)
{
    visitado[pt.x][pt.y] = false;
}

resolver_labirinto(pontoT pt)
{
    if (saiu_do_labirinto(pt)) return true;
    if (mapa[pt.x][pt.y] == '#' || esta_marcado(pt)) return false;

    marcar_ponto(pt);

    for (direcao dir = Norte; dir <= Oeste; dir++)
    {
        pontoT novo_pt = pt;
        
        switch (dir)
        {
            case Norte: novo_pt.x--; break;
            case Leste: novo_pt.y++; break;
            case Sul: novo_pt.x++; break;
            case Oeste: novo_pt.y--; break;
        }

        if (resolver_labirinto(novo_pt))
        {
            return true;
        }
    } 

    desmarcar_ponto(pt);
    
    return false;
}