#include "ponto.h"
#include <time.h>

ponto::ponto()
{
	x = 0;
	y = 0;
}
ponto::ponto(int mx, int my)
{
	x = mx;
	y = my;
}

ponto::~ponto()
{
}

void ponto::set_x(int a)
{
	x = a;
}
void ponto::set_y(int a)
{
	y = a;
}

void ponto::set_p(int _x, int _y) {
	x = _x;
	y = _y;
}

void ponto::set_p(ponto p){
	x = p.get_x();
	y = p.get_y();
}

void ponto::ask2set()
{
	cout << endl << "Insira a linha: ";
	cin >> x;
	cout << "Insira a coluna: ";
	cin >> y;
}

void ponto::showponto(void) {
	cout << "x=" << x << " y=" << y << endl;
}

bool ponto:: operator == (const ponto p)const{
	if (get_x() == p.get_x() && get_y() == p.get_y())
		return true;
	else
		return false;
}

bool ponto:: operator != (const ponto p)const {
	//if(this == p)
	if (get_x() != p.get_x() || get_y() != p.get_y())
		return false;
	else
		return true;
}

void ponto:: operator =(ponto p){
	x = p.get_x();
	y = p.get_y();
}

void ponto::save(ofstream &os) {
	os << '(' << get_x() << ',' << get_y() << ')' << ';'; // (x,y);
}


void ponto::read(ifstream &is) {
	char aux[10], a;

	do {
		is >> a;
	} while (a != '(');

	is.getline(aux, 9, ',');
	x = atoi(aux);

	is.getline(aux, 9, ')');
	y = atoi(aux);
}

void ponto::aleatorio(ponto *v, int dim) {
	srand(time(NULL));
	int i, pos;
	pos = rand() % dim;
	*this = v[pos];
}

void ponto::troca(ponto &p1) {
	int aux;
	
	aux = x;
	x = p1.get_x();
	p1.set_x(aux);

	aux = y;
	y = p1.get_y();
	p1.set_y(aux);
}