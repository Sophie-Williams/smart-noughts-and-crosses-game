#include "pessoa.h"



pessoa::pessoa()
{
	nome = "Maria";
	idade = 20;
}


pessoa::~pessoa()
{
}

pessoa::pessoa(string _nome, string _morada, Data _data_n)
{
	nome = _nome;
	morada = _morada;
	data_n = _data_n;
}

pessoa::pessoa(string _nome, string _morada, int _dia, int _mes, int _ano)
{
	nome = _nome;
	morada = _morada;
	data_n.Update(_dia, _mes, _ano);

}

void pessoa::show(void)
{
	cout << "Nome: " << nome << endl;
	cout << "Morada: " << morada << endl;
	cout << "Data de Nascimento: ";
	cout << data_n;
}

ostream & operator << (ostream &os, const pessoa x)
{
	os << x.nome << endl;
	os << x.morada << endl;
	os << x.data_n << endl;
	return os;
}

istream & operator >> (istream &is, pessoa &x)
{
	char aux[100];
	cout << "Nome: ";
	is.getline(aux, sizeof aux);
	x.nome = aux;
	cout << "Morada: ";
	is.getline(aux, sizeof aux);
	x.morada = aux;
	cout << "Data de Nascimento: ";
	is >> x.data_n;
	return is;
}

void pessoa::savefile(ofstream & os)
{
	os << nome << ";" << morada << ";" << data_n;
}

void pessoa::readfile(ifstream & is)
{
	char aux[100];
	is.getline(aux, 100, ';');
	nome = aux;
	data_n.ReadFile(is);
	is.getline(aux, 100, ';');
	morada = aux;
}


void pessoa::readk(void)
{
	char aux[100];
	cout << "Nome: ";
	cin.getline(aux, sizeof aux);
	nome = aux;
	fflush(stdin);
	cout << "Morada: ";
	cin.getline(aux, sizeof aux);
	morada = aux;
	fflush(stdin);
	cout << "Data de Nascimento: ";
	cin >> data_n;
}
