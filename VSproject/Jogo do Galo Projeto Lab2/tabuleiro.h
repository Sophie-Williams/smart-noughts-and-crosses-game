#pragma once
#include "ponto.h"
class tabuleiro
{
private:
	char **matriz;
	int nc, nl;
public:
	tabuleiro();
	tabuleiro(int, int);
	~tabuleiro();

	void set_nc(int mnc);
	void set_nl(int mnl);
	void set_cell(ponto, char);
	int get_nc() { return nc; }
	int get_nl() { return nl; }
	char get_cell(ponto);

	void inicia();
	void show();
	bool isfull();
	bool isvalide(int, int);
	
	void save(ofstream &os);
	void read(ifstream &is);

	int descobrir_espaços_vazios(ponto *v);
};

