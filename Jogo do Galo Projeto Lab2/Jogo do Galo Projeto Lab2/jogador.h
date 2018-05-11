#pragma once
#include "tabuleiro.h"
#include "pessoa.h"

class jogador : public pessoa
{
private:
	char simbolo;
	ponto jogadas[5];
	int n_jogadas;
	int id;
	int numjogos;
	int vitorias;
	int vitconsecutivas;
	int minutos;
	char classe;
	int valorexpert;
public:
	jogador();
	virtual ~jogador();
	void set_simbolo(char s) { simbolo = s; }
	void set_jogadas(ponto p, int i) { jogadas[i] = p; }
	void set_n_jogadas(int n) { n_jogadas = n; }
	char get_simbolo() { return simbolo; }

	ponto get_jogadas(int i) { return jogadas[i]; }
	int get_n_jogadas() { return n_jogadas; }

	int get_vitorias() { return vitorias; }
	int get_numjogos() { return numjogos; }

	void operator =(jogador jog);

	void jogada(tabuleiro *tab);

	void save(ofstream &os);
	void read(ifstream &is);

	int gerar_id(string nome);

	void show();

	virtual void jogada_pc(tabuleiro*);

	void login();
	bool procurar_dados();

	void atualizar_est(int, bool);
	void rank();

};


