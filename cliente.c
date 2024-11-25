#include "genlib.h"
#include "labirinto.h"
#include "simpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void)
{
    ler_mapa_labirinto("arquivo.txt");

    if(resolver_labirinto(pegar_posicao_inicial()))
        printf("As posicoes com X marcam o caminho para saida.\n");
    else
        printf("Nao existe saida do labirinto.\n");
}