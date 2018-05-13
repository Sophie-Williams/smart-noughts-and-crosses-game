#include "jogo.h"
#include <time.h>

jogo::jogo()
{
	tab = new tabuleiro;
}

jogo::~jogo()
{
	delete tab;
}

void jogo::random_simbolo(){
	srand(time(NULL));
	int r;
	r = rand() % 2;  //r = 1 ou 0

	if (r == 1) {
		jogador1.set_simbolo('X');
		jogador2.set_simbolo('O');
		jexp.set_simbolo('O');
	}
	else {
		jogador2.set_simbolo('X');
		jexp.set_simbolo('X');
		jogador1.set_simbolo('O');
	}
}


bool jogo::verifica_vitoria(char s){
	ponto p1, p2, p3;
	int i;

	for (i = 1;i <= 3;i++) {
		p1.set_x(i); p2.set_x(i); p3.set_x(i);
		p1.set_y(1); p2.set_y(2); p3.set_y(3);
		if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == s) //linhas
			return true;  //jogador ganhou

		p1.set_x(1); p2.set_x(2); p3.set_x(3);
		p1.set_y(i); p2.set_y(i); p3.set_y(i);
		if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == s) //colunas
			return true;  //jogador ganhou
	}
	p1.set_x(1); p2.set_x(2); p3.set_x(3);
	p1.set_y(1); p2.set_y(2); p3.set_y(3);
	if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == s) //diagonal
		return true;  //jogador ganhou
	p1.set_x(1); p2.set_x(2); p3.set_x(3);
	p1.set_y(3); p2.set_y(2); p3.set_y(1);
	if (tab->get_cell(p1) == s && tab->get_cell(p2) == s && tab->get_cell(p3) == s) //diagonal
		return true;  //jogador ganhou

	return false;
}

//bool Tabuleiro::vitoria(char _simbolo) {
//
//	int i, j, vcoluna, vlinha, vdia1, vdia2;
//
//	for (i = 0; i < 3; i++) {
//		vcoluna = vlinha = vdia1 = vdia2 = 0;
//		for (j = 0; j < 3; j++) {
//			if (Matriz[i][j] == _simbolo) { vcoluna = vcoluna + 1; }
//			else { vcoluna = 0; }
//
//			if (Matriz[j][i] == _simbolo) { vlinha = vlinha + 1; }
//			else { vlinha = 0; }
//
//			if (Matriz[j][j] == _simbolo) { vdia1 = vdia1 + 1; }
//			else { vdia1 = 0; }
//
//			if (Matriz[j][2 - j] == _simbolo) { vdia2 = vdia2 + 1; }
//			else { vdia2 = 0; }
//
//			if (vcoluna == 3 || vlinha == 3 || vdia1 == 3 || vdia2 == 3) {
//				return true;
//			}
//		}
//	}
//
//	return false;
//
//}

void jogo::gestão_jogo_j1_vs_j2() {
	jogador *first, *second;
	int vitoria = 0; //se vitoria=1 ganhou o first, se vitoria=2 ganhou second
	if (jogador1.get_simbolo() == 'X') {
		first = &jogador1;
		second = &jogador2;
		cout << "Comeca o jogador 1." << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}
	else {
		first = &jogador2;
		second = &jogador1;
		cout << "Comeca o jogador 2." << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}

	if (first->get_n_jogadas() > second->get_n_jogadas()) goto segundoajogar;
	//quando o jogo é retomado e foi deixado a meio e era a vez do segundo a jogar

	do {
		system("cls");
		tab->show();
		first->jogada(tab);
		guardar_jogo();
		system("cls");
		tab->show();
		if (verifica_vitoria(first->get_simbolo())) vitoria = 1;

	segundoajogar:
		system("cls");
		tab->show();
		if (vitoria == 0 && !tab->isfull()) {
			second->jogada(tab);
			guardar_jogo();
			system("cls");
			tab->show();
			if (verifica_vitoria(second->get_simbolo())) vitoria = 2;
		}
	} while (vitoria == 0 && !tab->isfull());

	if (jogador1.get_simbolo() == 'X') {
		switch (vitoria)
		{
		case 0:
			cout << "Jogo empatado." << endl;
			break;
		case 1:
			cout << "Jogador 1 ganhou." << endl;
			break;
		case 2:
			cout << "Jogador 2 ganhou." << endl;
			break;
		}
	}
	else {
		switch (vitoria)
		{
		case 0:
			cout << "Jogo empatado." << endl;
			break;
		case 1:
			cout << "Jogador 2 ganhou." << endl;
			break;
		case 2:
			cout << "Jogador 1 ganhou." << endl;
			break;
		}
	}

	guardar_jogo();
	numero_jogo++;
	system("pause");
}


void jogo::guardar_jogo() {
	ofstream os;
	char fich[10] = "jogo", aux[100];
	itoa(numero_jogo, aux, 99);       //passar numero_jogo para char
	strcat(fich, aux);               //juntar "jogo" + numero_jogo
	strcat(fich, ".txt");            //juntar .txt

	os.open(fich);                   //abrir o ficheiro feito em cima
	save(os);
	if (verifica_vitoria(jogador1.get_simbolo()) || verifica_vitoria(jogador2.get_simbolo()) || tab->isfull()) {
		os << "Jogo Finalizado." << endl;
		if (verifica_vitoria(jogador1.get_simbolo())) {          //para saber quem ganhou o jogo
			os << 1 << endl;
		}
		if (verifica_vitoria(jogador2.get_simbolo())) {
			os << 2 << endl;
		}
		if (tab->isfull()) {
			os << 0 << endl;       //reconhece como empate
		}
	}
	//escreve jogo finalizado no ficheiro pra saber que o jogo já acabou quando fizer read
	os.close(); 
}

void jogo::apagar_ficheiros() {    //como guarda todos os jogos, quando o utilizador quiser cmeçar nova sequencia de jogos
	char fich[10] = "jogo", aux[100];
	//apagar ficheiros com jogos anteriores
	for (int i = descobrir_numero_jogo_em_ficheiro(); i > 0;i--) {
		strcpy(fich, "jogo");
		itoa(i, aux, 99);      //passar numero_jogo para char
		strcat(fich, aux);     //juntar "jogo" + numero_jogo
		strcat(fich, ".txt");    //juntar .txt
		remove(fich);
	}
}

void jogo::iniciar_novo_jogo() {
	tab->inicia();
	random_simbolo();
	ponto p(0, 0);
	for (int i = 0;i < 5;i++) {
		jogador1.set_jogadas(p, i);
		jogador2.set_jogadas(p, i);
	}

	jogador1.set_n_jogadas(0);
	jogador2.set_n_jogadas(0);
}

void jogo::save(ofstream &os) {
	tab->save(os);
	os << "\nJogador1:\n";
	jogador1.save(os);
	os << "\nJogador2:\n";
	jogador2.save(os);
}

void jogo::read(ifstream &is) {
	char aux[30];
	tab->read(is);
	is.getline(aux, 29, '\n');
	is.getline(aux, 29, '\n');
	jogador1.read(is);
	is.getline(aux, 29, '\n');
	is.getline(aux, 29, '\n');
	jogador2.read(is);
}

bool jogo::retomar_jogo() {            //se for falso o jogo já foi finalizado
	numero_jogo = descobrir_numero_jogo_em_ficheiro();
	char fin[20];
	if (numero_jogo != 0) {
		ifstream is;
		char fich[10] = "jogo", aux[100];
		itoa(numero_jogo, aux, 99);       //passar numero_jogo para char
		strcat(fich, aux);               //juntar "jogo" + numero_jogo
		strcat(fich, ".txt");            //juntar .txt
		is.open(fich);
		read(is);
		is.getline(fin, 50, '\n');
		is.close();
		if (strcmp(fin, "Jogo Finalizado.") == 0) return false;     //o jogo já foi finalizado
		return true;
	}
	return false;    //não há jogos para retomar
}

int jogo::descobrir_numero_jogo_em_ficheiro() {
	ifstream is;
	char fich[10], aux[100];
	int i, n_jogo;
	bool f=true;
	//existem vários ficheiros, temos de utilizar o que tem o numero de jogo menos elevado
	//objetivo: abrir ficheiros de jogo e ver qual é o ultimo a partir do nome
	//o seguinte nao vai existir
	//ver qual nao ixiste:
	for (i = 1; f ;i++) {
		strcpy(fich, "jogo");
		itoa(i, aux, 99);      //passar numero_jogo para char
		strcat(fich, aux);     //juntar "jogo" + numero_jogo
		strcat(fich, ".txt");    //juntar .txt
		is.open(fich);             //abrir o ficheiro 
		if (!is) f = false;                   //f é falso quando o ficheiro não abrir
		is.close();
	}
	

	n_jogo = i - 2;
	return n_jogo;
}

void jogo::jogador1_vs_jogador2() {
	ifstream is;
	char fich[10] = "jogo", aux[100];
	int a, vit1 = 0, vit2 = 0, empates = 0;

	for (int i = descobrir_numero_jogo_em_ficheiro(); i > 0;i--) {
		strcpy(fich, "jogo");
		itoa(i, aux, 99);      //passar numero_jogo para char
		strcat(fich, aux);     //juntar "jogo" + numero_jogo
		strcat(fich, ".txt");    //juntar .txt
		is.open(fich);
		read(is);
		is.getline(aux, 50, '\n');
		is >> a;
		is.close();
		switch (a){
		case 0:
			empates++;
			break;
		case 1:
			vit1++;
			break;
		case 2:
			vit2++;
			break;
		}
	}
	cout << "Vitorias jogador 1: " << vit1 << endl;
	cout << "Vitorias jogador 2: " << vit2 << endl;
	cout << "Empates: " << empates << endl;
	system("pause");
}


void jogo:: modo2facil() {
	int min=0;
	jogador *first, *second;
	jogador1.login();
	int vitoria = 0; //se vitoria=1 ganhou o first, se vitoria=2 ganhou second
	if (jogador1.get_simbolo() == 'X') {
		first = &jogador1;
		second = &jogador2;                        //jogador 2 é o computador
		cout << "Comecas tu " << jogador1.get_nome() << "!" << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}
	else {
		first = &jogador2;
		second = &jogador1;
		cout << "Comeca o computador." << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}

	time_t m;
	m = time(NULL);

	if (first->get_n_jogadas() > second->get_n_jogadas()) goto segundoajogar;
	//quando o jogo é retomado e foi deixado a meio e era a vez do segundo a jogar

	do {
		system("cls");
		tab->show();
		if (first == &jogador1) first->jogada(tab);
		else first->jogada_pc(tab);
		//guardar_jogo();
		system("cls");
		tab->show();
		if (verifica_vitoria(first->get_simbolo())) vitoria = 1;

	segundoajogar:
		system("cls");
		tab->show();
		if (vitoria == 0 && !tab->isfull()) {
			if (second == &jogador1) second->jogada(tab);
			else second->jogada_pc(tab);
			//guardar_jogo();
			system("cls");
			tab->show();
			if (verifica_vitoria(second->get_simbolo())) vitoria = 2;
		}
	} while (vitoria == 0 && !tab->isfull());

	min = time(NULL) - m;

	if (jogador1.get_simbolo() == 'X') {
		switch (vitoria)
		{
		case 0:
			cout << "Jogo empatado." << endl;
			break;
		case 1:
			cout << jogador1.get_nome() << " ganhou, parabéns." << endl;
			break;
		case 2:
			cout << "Computador ganhou." << endl;
			break;
		}
	}
	else {
		switch (vitoria)
		{
		case 0:
			cout << "Jogo empatado." << endl;
			jogador1.atualizar_est(min, false);
			break;
		case 1:
			cout << "Computador ganhou." << endl;
			jogador1.atualizar_est(min, false);
			break;
		case 2:
			cout << "Jogador 1 ganhou." << endl;
			jogador1.atualizar_est(min, true);
			break;
		}
	}

	system("pause");
}


void jogo::modo2expert() {
	jogador *first, *second;
	int min = 0;
	int vitoria = 0; //se vitoria=1 ganhou o first, se vitoria=2 ganhou second
	jogador1.login();
	if (jogador1.get_simbolo() == 'X') {
		first = &jogador1;
		second = &jexp;                        //jogador 2 é o computador
		cout << "Comecas tu " << jogador1.get_nome() << "!" << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}
	else {
		first = &jexp;
		second = &jogador1;
		cout << "Comeca o computador." << endl;
		cout << "Prima qualquer tecla para comecar o jogo." << endl;
		system("pause>null");
	}
	time_t m;
	m = time(NULL);

	if (first->get_n_jogadas() > second->get_n_jogadas()) goto segundoajogar;
	//quando o jogo é retomado e foi deixado a meio e era a vez do segundo a jogar

	do {
		system("cls");
		tab->show();
		if (first == &jogador1) first->jogada(tab);
		else first->jogada_pc(tab);
		//guardar_jogo();
		system("cls");
		tab->show();
		if (verifica_vitoria(first->get_simbolo())) vitoria = 1;

	segundoajogar:
		system("cls");
		tab->show();
		if (vitoria == 0 && !tab->isfull()) {
			if (second == &jogador1) second->jogada(tab);
			else second->jogada_pc(tab);
			//guardar_jogo();
			system("cls");
			tab->show();
			if (verifica_vitoria(second->get_simbolo())) vitoria = 2;
		}
	} while (vitoria == 0 && !tab->isfull());

	min = time(NULL) - m;

	if (jogador1.get_simbolo() == 'X') {
		switch (vitoria)
		{
		case 0:
			cout << "Jogo empatado." << endl;
			jogador1.atualizar_est(min, false);
			break;
		case 1:
			cout << "Jogador 1 ganhou." << endl;
			jogador1.atualizar_est(min, true);
			break;
		case 2:
			cout << "Computador ganhou." << endl;
			jogador1.atualizar_est(min, false);
			break;
		}
	}
	else {
		switch (vitoria)
		{
		case 0:
			jogador1.atualizar_est(min, false);
			cout << "Jogo empatado." << endl;
			break;
		case 1:
			jogador1.atualizar_est(min, false);
			cout << "Computador ganhou." << endl;
			break;
		case 2:
			jogador1.atualizar_est(min, true);
			cout << "Jogador 1 ganhou." << endl;
			break;
		}
	}

	system("pause");
}

void jogo::campeonato10jogos() {

	apagar_ficheiros();
	set_numero_jogo(1);
	
	for (int i = 0;i < 2;i++) {
		iniciar_novo_jogo();
		gestão_jogo_j1_vs_j2();
	}

	jogador1_vs_jogador2();
}

