#include "menu.h"


menu::menu()
{
}


menu::~menu()
{
}

void menu::show_manual_utilizador() {
	system("cls");
	cout << "Manual de utilizador:" << endl;
	cout << "- O simbolo 'X' joga sempre primeiro e os simbolos 'X' e 'O' são sempre atribuidos aleatoriamente." << endl;
	cout << "- Cada jogador joga uma marca de cada vez em uma posição livre." << endl;
	cout << "- Para ganhar o jogo e necessário conseguir 3 circulos ou tres Xs numa linha horizontal, na vertical ou na diagonal." << endl;

	cout << "\nPrima qualquer tecla para ir para o menu." << endl;
	system("pause>null");
}

void menu::show_regras() {
	system("cls");
	cout << "Regras do jogo:" << endl;
	cout << "- O tabuleiro materializado por uma matriz com tres linhas e tres colunas (Tabuleiro[3][3])." << endl;
	cout << "- Aos dois jogadores e lhes atribuida uma marca a cada um, usualmente utiliza - se um X (X) e um circulo(O)." << endl;
	cout << "- Quando um jogador vence e apresentada uma mensagem indicando a vitoria  do respetivo jogador." << endl;
	cout << "- '.' Representa um espaço vazio." << endl;
	cout << "- 'O' Representa o símbolo utilizado por um jogador." << endl;
	cout << "- 'X' Representa o símbolo utilizado pelo outro jogador." << endl;
	cout << "- Um jogador ganha quando faz uma linha, coluna ou diagonal com o simbolo que lhe foi atribuido: Exemplo:" << endl;
	cout << "    X | X | X      X | . | .       . | X | ." << endl;
	cout << "    . | . | .      . | X | .       . | X | ." << endl;
	cout << "    . | . | .      . | . | X       . | X | ." << endl;

	cout << "\nPrima qualquer tecla para ir para o menu." << endl;
	system("pause>null");
}


void menu::show() {
	system("cls");
	cout << endl << "     Menu:" << endl << endl;
	cout << "     Insira a letra correspondente a sua opcao:" << endl << endl;
	cout << "     Modo 1 - jogador1 vs jogador2:" << endl;
	cout << "\t   1 - Comecar Novo jogo (apagar jogos anteriores)." << endl;

	if (j.retomar_jogo()) {
		cout << "\t   2 - Retomar jogo numero " << j.get_numero_jogo() << " (Load Mode)." << endl;
		cout << "\t   3 - Nao e possivel continuar a sequencia de jogos sem acabar o ultimo jogo." << endl;
	}
	else {
		cout << "\t   2 - Nao ha nenhum jogo para retomar." << endl;

		if (j.descobrir_numero_jogo_em_ficheiro() != 0) {
			cout << "\t   3 - Comecar jogo numero " << j.get_numero_jogo() + 1 << " (Load Mode)." << endl;
		}
		else {
			cout << "\t   3 - Não há jogos anteriores." << endl;
		}
	}
	cout << "\t   4 - Mostrar resultados Jogador1 vs Jogador2 nesta sequencia de jogos." << endl << endl;

	cout << "     Modo 2 - Jogador vs Computador: (Login necessario)" << endl;
	cout << "\t   5 - Comecar novo jogo." << endl; //depois de entrar e fazer login diz se tem jogo para retomar
	cout << "\t   6 - Campeonato de 10 jogos." << endl;

	cout << "     ---------------------------------------------------" << endl << endl;
	cout << "\t   7 - Mostrar Regras do jogo." << endl;
	cout << "\t   8 - Mostrar Manual de Utilizador." << endl;

	cout << "\t   9 - Sair." << endl << endl;
	cout << "Opcao: ";
}


//o jogador pode retomar um jogo, continuar sequencia de jogos, ou começar novo jogo 
//(R(retomar), C(continuar), N(novo jogo), S(sair))
void menu::executar() {
	int n;
	do {
		show();
		fflush(stdin);
		cin >> opcao;
	} while (!((opcao == 1) || (opcao == 2 && j.retomar_jogo()) ||
		(opcao == 3 && j.descobrir_numero_jogo_em_ficheiro() != 0 && !j.retomar_jogo()) || (opcao == 4) 
		|| (opcao == 5) || (opcao == 6) || (opcao == 7) ||
		(opcao == 8) || (opcao == 9) ));

	while (opcao != 9) {     
		switch (opcao)
		{
		case 1:
			j.set_numero_jogo(1);
			j.apagar_ficheiros();
			j.iniciar_novo_jogo();
			j.gestão_jogo_j1_vs_j2();
			break;
		case 2:
			j.retomar_jogo();
			j.gestão_jogo_j1_vs_j2();
			break;
		case 3:
			j.iniciar_novo_jogo();
			n = j.descobrir_numero_jogo_em_ficheiro() + 1;
			j.set_numero_jogo(n);
			j.gestão_jogo_j1_vs_j2();
			break;
		case 4:
			j.jogador1_vs_jogador2();
			break;
		case 5:
			j.iniciar_novo_jogo();
			gerir_dificuldade();
			break;
		case 6:
			j.campeonato10jogos();
			break;
		case 7:
			show_regras();
			break;
		case 8:
			show_manual_utilizador();
			break;
		}
		do {
			show();
			cin >> opcao;
		} while (!((opcao == 1) || (opcao == 2 && j.retomar_jogo()) ||
			(opcao == 3 && j.descobrir_numero_jogo_em_ficheiro() != 0 && !j.retomar_jogo()) || (opcao == 4)
			|| (opcao == 5) || (opcao == 6) || (opcao == 7) ||
			(opcao == 8)));
	}
}


void menu::gerir_dificuldade() {
	int d;
	do {
	system("cls");
	cout << "Selecione a dificuldade: " << endl;
	cout << "1 - Facil " << endl;
	cout << "2 - Expert " << endl;
	cin >> d;
	} while (d != 1 && d != 2 );


	switch (d) {
	case 1:
		j.modo2facil();
		break;
	case 2:
		j.modo2expert();
		break;
	}
}
