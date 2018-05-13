#pragma once
#include <string>
#include <iostream>
#include "Data.h"

using namespace std;
class pessoa
{
private:
	string nome;
	int idade;
	string morada;
	Data data_n;
public:
	pessoa();
	int get_idade() { return idade; }
	void set_nome(string n) { nome = n; }
	void set_idade(int _idade) { idade = _idade; }

	pessoa(string _nome, string _morada, Data _data_n);
	pessoa(string _nome, string _morada, int _dia, int _mes, int _ano);
	virtual ~pessoa();
	void setnome(string _nome) { nome = _nome; }
	void setmorada(string _morada) { morada = _morada; }
	void setdata(Data _data_n) { data_n = _data_n; }
	Data get_data(void) { return data_n; }
	string get_nome(void) { return nome; }
	string get_morada(void) { return morada; }
	virtual void show(void);
	friend ostream & operator << (ostream &os, const pessoa x);
	friend istream & operator >> (istream &is, pessoa &x);
	virtual void savefile(ofstream &os);
	virtual void readfile(ifstream &is);
	virtual void readk(void);
};

