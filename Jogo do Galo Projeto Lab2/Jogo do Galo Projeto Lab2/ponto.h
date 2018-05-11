#pragma once
#include <iostream>
#include "stdafx.h"
#include <fstream>
#include <string>
using namespace std;

class ponto
{
private:
	int x, y;

public:
	ponto();
	ponto(int, int);
	~ponto();
	void set_x(int a);
	void set_y(int a);
	void set_p(int, int);
	void set_p(ponto p);
	void ask2set();

	int get_x()const{ return x; }
	int get_y()const{ return y; }

	//bool isvalid(void);        este método esquandra-se melhor na classe tabuleiro
	void showponto(void);

	bool operator == (const ponto p)const;
	bool operator != (const ponto p)const;
	void operator = (ponto p);

	void save(ofstream &os);
	void read(ifstream &is);
	void aleatorio(ponto *v, int dim);
	void troca(ponto&);
};