/**
 * Arquivo: labirinto.c
 * −−−−−−−−−−−−−−−−−−−−−−−−−
 * Este arquivo implementa a interface 'labirinto.h',
 * utilizando procedimentos recursivos de backtracking.
 *
 * Baseado em: Programming Abstractions in C, de Eric S. Roberts.
 * Capítulo 6: Backtracking Algorithms (pg. 235−245).
 *
 * Prof.: Abrantes Araújo Silva Filho
 * Computação Raiz:
 * www.computacaoraiz.com.br
 * www.youtube.com.br/computacaoraiz
 * github.com/computacaoraiz
 * twitter.com/ComputacaoRaiz
 * www.linkedin.com/company/computacaoraiz
 * www.abrantes.pro.br
 */

/* Includes */
#include "labirinto.h"
#include "genlib.h"
#include "simpio.h"

/* Defines */
#define MAX_LINHAS 100
#define MAX_COLUNAS 100

/* Criação de variáveis */
char mapa[MAX_LINHAS][MAX_COLUNAS];
bool visitado[MAX_LINHAS][MAX_COLUNAS];
int linhas = 0, colunas = 0;
pontoT posicao_inicial;

/**
 * Procedimento: ler_mapa
 * Uso: ler_mapa(arquivo);
 * -----------------------
 * Este procedimento lê o mapa do labirinto a partir de um arquivo
 * passado como argumento. O mapa é armazenado na variável global `mapa`.
 * Ele também localiza a posição inicial indicada pelo caractere 'I' e
 * armazena suas coordenadas em `posicao_inicial`.
 */
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
        mapa[linhas][strcspn(mapa[linhas], "\n")] = '\0';
        colunas = strlen(mapa[linhas]);
        linhas++;
    }
    fclose(file);

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (mapa[i][j] == 'I')
            {
                posicao_inicial.x = i;
                posicao_inicial.y = j;

                return;
            }
        }
    }
}

/**
 * Função: pegar_posicao_inicial
 * Uso: pontoT inicio = pegar_posicao_inicial();
 * --------------------------------------------
 * Retorna a posição inicial do labirinto, identificada pela leitura do
 * caractere 'I'.
 */
pontoT pegar_posicao_inicial(void)
{
    return posicao_inicial;
}

/**
 * Predicado: saiu_do_labirinto
 * Uso: if (saiu_do_labirinto(pt)) ...
 * -----------------------------------
 * Retorna `true` se o ponto especificado está fora dos limites do labirinto.
 */
bool saiu_do_labirinto(pontoT pt)
{
    return pt.x < 0 || pt.x >= linhas || pt.y < 0 || pt.y >= colunas;
}

/**
 * Predicado: e_parede
 * Uso: if (e_parede(pt, dir)) ...
 * --------------------------------
 * Retorna `true` se houver uma parede ou obstáculo na direção indicada
 * a partir do ponto especificado.
 */
bool e_parede(pontoT pt, direcaoT dir)
{
    pontoT novo_pt = pt;

    switch (dir)
    {
        case Norte: novo_pt.x--; break;
        case Leste: novo_pt.y++; break;
        case Sul: novo_pt.x++; break;
        case Oeste: novo_pt.y--; break;
    }

    if (saiu_do_labirinto(novo_pt)) return true;

    return mapa[novo_pt.x][novo_pt.y] == '#' || mapa[novo_pt.x][novo_pt.y] == '|' || mapa[novo_pt.x][novo_pt.y] == '-' || mapa[novo_pt.x][novo_pt.y] == '+';
}

/**
 * Predicado: esta_marcado
 * Uso: if (esta_marcado(pt)) ...
 * ------------------------------
 * Retorna `true` se o ponto especificado já foi visitado.
 */
bool esta_marcado(pontoT pt)
{
    return visitado[pt.x][pt.y];
}

/**
 * Procedimento: marcar_ponto
 * Uso: marcar_ponto(pt);
 * ----------------------
 * Marca um ponto como visitado e atualiza o mapa para incluir o caractere 'X'
 * na posição especificada, desde que não seja um obstáculo do tipo '+'.
 */
void marcar_ponto(pontoT pt)
{
    if (mapa[pt.x][pt.y] != '+') { // Não sobrescreve quinas
        visitado[pt.x][pt.y] = true;
        mapa[pt.x][pt.y] = 'X';
    }
}

/**
 * Procedimento: desmarcar_ponto
 * Uso: desmarcar_ponto(pt);
 * --------------------------
 * Desmarca um ponto, removendo-o da lista de pontos visitados, e restaura
 * o caractere original no mapa.
 */
void desmarcar_ponto(pontoT pt)
{
    visitado[pt.x][pt.y] = false;
    mapa[pt.x][pt.y] = ' ';
}

/**
 * Função: resolver_labirinto
 * Uso: if (resolver_labirinto(pt)) ...
 * ------------------------------------
 * Resolve o labirinto recursivamente usando backtracking. Marca os pontos do
 * caminho com 'X' e retorna `true` se o labirinto pode ser resolvido a partir
 * do ponto inicial, ou `false` caso contrário.
 */
bool resolver_labirinto(pontoT pt)
{
    if (saiu_do_labirinto(pt)) return true;
    if (mapa[pt.x][pt.y] == '#' || mapa[pt.x][pt.y] == '|' || mapa[pt.x][pt.y] == '-' || mapa[pt.x][pt.y] == '+' || esta_marcado(pt)) return false;
    

    marcar_ponto(pt);

    for (direcaoT dir = Norte; dir <= Oeste; dir++)
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

/**
 * Procedimento: imprimir_mapa
 * Uso: imprimir_mapa();
 * ----------------------
 * Imprime o mapa do labirinto no estado atual, incluindo as marcações
 * feitas pelo algoritmo de resolução.
 */
void imprimir_mapa(void)
{
    for (int i = 0; i < linhas; i++)
    {
        printf("%s\n", mapa[i]);
    }
}
