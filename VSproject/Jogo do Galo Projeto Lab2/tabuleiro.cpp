#include "tabuleiro.h"

tabuleiro::tabuleiro()
{
	int i;
	nc = 3;
	nl = 3;
	matriz = new char*[nl];
	for (i = 0; i < nl; i++) {
		matriz[i] = new char[nc];
	}
	inicia();
}

tabuleiro::tabuleiro(int mnc, int mnl)
{
	int i;
	nc = mnc;
	nl = mnl;
	matriz = new char*[nl];
	for (i = 0; i < nl; i++) {
		matriz[i] = new char[nc];
	}
	inicia();
}

tabuleiro::~tabuleiro()
{
	for (int i = 0; i < nl; i++) {
		delete matriz[i];
	}
	delete matriz;
}

void tabuleiro::set_nc(int mnc) {
	nc = mnc;
}

void tabuleiro::set_nl(int mnl) {
	nl = mnl;
}

void tabuleiro::set_cell(ponto p, char simbolo) {
	matriz[p.get_x() - 1][p.get_y() - 1] = simbolo;
}

char tabuleiro::get_cell(ponto p) {
	return matriz[p.get_x() - 1][p.get_y() - 1];
}


void tabuleiro::inicia() {
	cout << "\n";
	int i, j;
	for (i = 0; i < nl; i++) {
		for (j = 0; j < nc; j++) {
			matriz[i][j] = '.';
		}
	}
}


void tabuleiro::show() {
	int i = 0, j;
	cout << "          Jogo do Galo\n";
	for (i = 0; i < nc; i++) {
		cout << "       " << i + 1;
	}
	cout << "\n";
	for (i = 0; i < nl; i++) {
		cout << i + 1 << "      ";
		for (j = 0; j < nc - 1; j++) {
			cout << matriz[i][j] << "   |   ";
		}
		cout << matriz[i][nc - 1];
		cout << "\n";
		if (i < nl - 1) {
			cout << "    -------";
			for (j = 0; j < nc - 1; j++) {
				cout << "|-------";
			}
			cout << "\n";
		}
	}
	cout << "\n";
}


bool tabuleiro::isfull() {
	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			if (matriz[i][j] == '.')
			{
				return false;
			}
		}
	}
	return true;
}


bool tabuleiro::isvalide(int mx, int my) {
	if (mx <= nl && mx > 0 && my <= nc && my > 0) {
		if (matriz[mx - 1][my - 1] == '.')
			return true;
		else
		{
			return false;
		}
	}
	else
		return false;
}




void tabuleiro::save(ofstream &os) {
	os << "matriz:" << nc << '/' << nl << endl;
	for (int i = 0;i < 3;i++)
	os << matriz[i][0] << '|' << matriz[i][1] << '|' << matriz[i][2] << endl;
}

void tabuleiro::read(ifstream &is) {
	char a, aux[10];
	do {
		is >> a;
	} while (a != ':');
	is >> nc;
	is >> a; // ler barra
	is >> nl;
	is.getline(aux, 9, '\n');
	for (int i = 0;i < 3;i++) {
		is >> matriz[i][0];
		is >> a; //ler barra
		is >> matriz[i][1];
		is >> a; //ler barra
		is >> matriz[i][2];
	    is.getline(aux, 9 , '\n');
	}
}


int tabuleiro::descobrir_espaços_vazios(ponto *v) {      //retorna o numero de espaços vazios e *v vai armazenar quais
	ponto p;
	int i, count = 0;

	for (i=1;i <= 3;i++) {
		for (int j=1;j <= 3;j++) {
			p.set_x(i); p.set_y(j);
			if (get_cell(p) == '.') {
				v[count] = p;
				count++;
			}
		}
	}
	return count;
}
