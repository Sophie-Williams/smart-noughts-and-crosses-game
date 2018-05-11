#include "jogadorexpert.h"



jogadorexpert::jogadorexpert()
{
}


jogadorexpert::~jogadorexpert()
{
}


bool jogadorexpert::vitoria_eminente(char s, ponto *p, tabuleiro *tab) {
	ponto p1, p2, p3;
	int i, j;


	for (i = 1;i <= 3;i++) {

		for (j = 1;j <= 3;j++) {
			p1.set_x(j); p2.set_x(j); p3.set_x(j);
			p1.set_y(1); p2.set_y(2); p3.set_y(3);
			if (i == 2) p1.troca(p3);
			if (i == 3) p2.troca(p3);
			if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == '.') { //linhas
				*p = p3;
				return true;
			}
		}

		for (j = 1;j <= 3;j++) {
			p1.set_x(1); p2.set_x(2); p3.set_x(3);
			p1.set_y(j); p2.set_y(j); p3.set_y(j);
			if (i == 2) p1.troca(p3);
			if (i == 3) p2.troca(p3);
			if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == '.') { //colunas
				*p = p3;
				return true;
			}
		}

		p1.set_x(1); p2.set_x(2); p3.set_x(3);
		p1.set_y(1); p2.set_y(2); p3.set_y(3);
		if (i == 2) p1.troca(p3);
		if (i == 3) p2.troca(p3);
		if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == '.') { //diagonal
			*p = p3;
			return true;
		}

		p1.set_x(1); p2.set_x(2); p3.set_x(3);
		p1.set_y(3); p2.set_y(2); p3.set_y(1);
		if (i == 2) p1.troca(p3);
		if (i == 3) p2.troca(p3);
		if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == '.') {//diagonal
			*p = p3;
			return true;
		}
	}

	return false;
}

void jogadorexpert::jogada_pc(tabuleiro *tab) {
	ponto p, v[9];
	int dim;
	char simbolo_adv;
	if (get_simbolo() == 'X') simbolo_adv = 'O';
	else simbolo_adv = 'X';

	do
	{
		if (vitoria_eminente(get_simbolo(), &p, tab));     //se tiver quase a ganhar ganha
		else {
			if (vitoria_eminente(simbolo_adv, &p, tab));    //senão se o adv tiver quase a ganhar nao deixa
			else
			{
				dim = tab->descobrir_espaços_vazios(v);
				p.aleatorio(v, dim);
			}                  //se ng tiver quase a ganhar joga aleatorio
		}

	} while (!tab->isvalide(p.get_x(), p.get_y()));
	tab->set_cell(p, get_simbolo());
	set_jogadas(p, get_n_jogadas());
	set_n_jogadas(get_n_jogadas()+1);
}

