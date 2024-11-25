#ifndef _LABIRINTO_H
#define _LABIRINTO_H

#include "genlib.h"
#include "simpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct st_pontoT pontoT;

typedef enum en_direcaoT direcaoT;

void ler_mapa(string arquivo);

pontoT pegar_posicao_inicial(void);

bool saiu_do_labirinto(pontoT pt);

bool e_parede(ponto pt, direcaoT dir);

bool esta_marcado(pontoT pt);

void marcar_ponto(pontoT pt);

void desmarcar_ponto(pontoT pt);

bool resolver_labirinto(pontoT pt);

#endif