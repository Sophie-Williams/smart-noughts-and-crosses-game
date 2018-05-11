#pragma once
#include "jogador.h"

class jogadorexpert: public jogador
{
public:
	jogadorexpert();
	virtual ~jogadorexpert();

	virtual void jogada_pc(tabuleiro*);
	bool vitoria_eminente(char, ponto*, tabuleiro*);
};

