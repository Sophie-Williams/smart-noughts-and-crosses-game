#pragma once
#include "jogo.h"
class menu
{
	int opcao;
	jogo j;
public:
	menu();
	~menu();

	int get_opção() { return opcao; }
	jogo get_jogo() { return j; }
	void set_opção(int d) { opcao = d; }
	
	void executar();

	void show();
	void show_regras();
	void show_manual_utilizador();
	
	void gerir_dificuldade();
};