#include "jogador.h"

jogador::jogador()
{
	n_jogadas = 0;
}

jogador::~jogador()
{
}

void jogador::jogada(tabuleiro *tab) {
	ponto p;

	do
	{
		p.ask2set();
	} while (!tab->isvalide(p.get_x(), p.get_y()));
	tab->set_cell(p, simbolo);
	jogadas[n_jogadas] = p;
	n_jogadas++;
}

void jogador:: operator =(jogador jog) {
	simbolo = jog.get_simbolo();
	set_nome(jog.get_nome());
	for (int i = 0;i < 5;i++) jogadas[i] = jog.get_jogadas(i);
	n_jogadas = jog.get_n_jogadas();
}

void jogador::save(ofstream &os) {
	os << simbolo << '/' << get_nome() << '/' << n_jogadas << endl; 
	for (int i = 0;i < 5;i++)
		jogadas[i].save(os);
	os << '\n';
}


void jogador::read(ifstream &is) {
	char aux[10], a;
	
	is >> simbolo;
	is >> a;
	is.getline(aux, 9, '/');
	set_nome(aux);
	is >> n_jogadas;
	is.getline(aux, 9, '\n'); // ler \n
	for (int i = 0;i < 5;i++)
		jogadas[i].read(is);
	is.getline(aux, 9, '\n'); // ler \n
}

void jogador::show() {
	pessoa::show();
	cout << "Simbolo: " << simbolo << endl;
}


void jogador::jogada_pc(tabuleiro *tab) {
	int dim;
	ponto p, v[9];
	do
	{
		dim = tab->descobrir_espaços_vazios(v);
		p.aleatorio(v, dim);
	} while (!tab->isvalide(p.get_x(), p.get_y()));
	tab->set_cell(p, simbolo);
	jogadas[n_jogadas] = p;
	n_jogadas++;
}

int jogador::gerar_id(string nome) {
	int cod, prox = 0;
	char aux[50];
	ifstream is;
	ofstream os;

	is.open("utilizadores.txt");
	if (!is) {                           //caso o ficheiro não exista cria um e começa a inserção
		os.open("utilizadores.txt");
		cod = 1000;
		os << cod << ";" << nome << ";" << 0 << ";" << 0 << ";" << 0 << ";" << 0 << ";" << 'B' << ";" << 0 << endl;
		os.close();
		return cod;
	}

	do {
		cod = prox;
		is.getline(aux, 49, ';');
		prox = atoi(aux);
		is.getline(aux, 49, '\n');
	} while (prox > cod);

	is.close();
	cod++;
	os.open("utilizadores.txt", ios_base::app);
	os << cod << ";" << nome << ";" << 0 << ";" << 0 << ";" << 0 << ";" << 0 << ";" << 'B' << ";" << 0 << endl;
	// id nome numjogos vitorias vitconsecutivas minutos classe valorexpert
	os.close();
	return cod;
}

bool jogador::procurar_dados() {
	ofstream os;
	ifstream is;
	char aux[50];
	int teste=0, linha=0, i;
	is.open("utilizadores.txt");  //para ver se o ficheiro existe
	if (!is) {
		cout << "ID nao existe." << endl;
		return false;
	}
	
	while (teste != id && !is.eof()) {
		linha++;
		is.getline(aux, 49, ';');
		teste = atoi(aux);
		is.getline(aux, 49, '\n');
	}
	if (teste != id) {
		cout << "ID nao existe." << endl;
		is.close();
		return false;
	}
	else {
		is.seekg(0, is.beg);
		for (i = 1;i < linha;i++) is.getline(aux, 49, '\n');
		is.getline(aux, 49, ';');   //ler codigo
		is.getline(aux, 49, ';');   //ler nome
		set_nome(aux);
		is >> numjogos;      //ler num jogos
		is.getline(aux, 3, ';');  

		is >> vitorias;      //ler vitorias
		is.getline(aux, 3, ';');  

		is >> vitconsecutivas;      //ler v consecutivas
		is.getline(aux, 3, ';');   

		is >> minutos;      //ler minutos
		is.getline(aux, 3, ';');   

		is >> classe;      //ler classe
		is.getline(aux, 3, ';');   
		
		is >> valorexpert;    //ler valor expert

		is.close();
		return true;
	}
}

void jogador::login() {
	bool login=false;
	ifstream is;
	string st;

	do {
		cout << "Insira o seu ID. (Se ainda não tem um ID insira 0 para ser gerado um novo ID para si.)" << endl;
		cin >> id;

		if (id == 0) {
			cout << "Qual é o seu nome?";
			cin >> st;
			set_nome(st);
			id = gerar_id(st);
			cout << "Foi gerado um novo id para si, o seu id e " << id << "." << endl;
		}
			login = procurar_dados();

	} while (!login);

	cout << "Ola " << get_nome() << endl;
	system("pause");

}

void jogador::atualizar_est(int minutos_ultimo, bool vitoria) {
	//copiar ficheiro para matriz de char
	//abrir e por tudo até á linha
	//por a linha
	//por o resto
	//incrementar jogo
	//acrescentar minutos
	char aux[100][100], aux2[100];
	ifstream is;
	ofstream os;
	int li=0;
	is.open("utilizadores.txt");

	for (int i = 0;!is.eof();i++) {
		is.getline(aux[i], 99, '\n');
		li++;
	}
	is.close();

	os.open("utilizadores.txt");
	for (int i = 0; i < id - 1000;i++)
		os << aux[i] << endl; //guarda até estar na linha certa
	
	numjogos++;
	if (vitoria) {
		vitorias++; 
		vitconsecutivas++;
	}
	else {
		vitconsecutivas = 0;
	}
	minutos += minutos_ultimo;

	rank();


	os << id << ";" << get_nome() << ";" << numjogos << ";" << vitorias << ";" << vitconsecutivas << ";" << minutos << ";" << classe << ";" << valorexpert << endl;
	// id nome numjogos vitorias vitconsecutivas minutos classe valorexpert

	for (int i = id - 998; i<li;i++) os << aux[i] << endl;
	os.close();
}

void jogador::rank() {
	//depende de numjogos, numvitorias, minutos, valorexpert
	if (classe == 'B' && vitconsecutivas == 5) {
		classe = 'E';
		cout << "Parabéns, voce e EXPERT NIVEL 1" << endl;
	}
	int min;
	//minutos em segundos  numjogos numvitorias
	min= minutos / 60;

	if (classe == 'E') {
	valorexpert = (vitorias * 5)/ (minutos + numjogos);
	}
	if (valorexpert < 1) valorexpert = 1;
	if (valorexpert > 10) valorexpert = 10;

}



