#pragma once
#include "jogador.h"
#include "jogadorexpert.h"

class jogo
{
private:
	tabuleiro *tab;
	jogador jogador1, jogador2;
	jogadorexpert jexp;
	int numero_jogo;
public:
	jogo();
	~jogo();
	void set_numero_jogo(int n) { numero_jogo = n; }
	void set_jogador1(jogador j1) { jogador1 = j1; }
	void set_jogador2(jogador j2) { jogador1 = j2; }
	void set_tab(tabuleiro _tab) { tab = &_tab; }

	jogador get_jogador1() { return jogador1; };
	jogador get_jogador2() { return jogador2; };
	int get_numero_jogo() { return numero_jogo; };
	tabuleiro * get_tab() { return tab; }
	
	void random_simbolo();

	void iniciar_novo_jogo();
	void gestão_jogo_j1_vs_j2();
	bool verifica_vitoria(char s);
	
	void save(ofstream &os);
	void read(ifstream &is);

	int descobrir_numero_jogo_em_ficheiro();
	void apagar_ficheiros();
	void guardar_jogo();
	bool retomar_jogo();
	void jogador1_vs_jogador2();

	void modo2facil();
	void modo2expert();
	void campeonato10jogos();
};

