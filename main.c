#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VAGAS 5

typedef enum { false, true } bool;
struct tdados{
	int hora, minuto;
	int ano, mes, dia;
	char placa[8];
	bool esta;
};
void menu ();
void identidade(struct tdados *p);
void entrada(struct tdados *p);
int bissexto(int ano);
int d_dias(struct tdados *p, struct tdados *q);
void cobrar(struct tdados *p, struct tdados *q, int dias);
char confirma(char message[]);
void main () {
	struct tdados dados[VAGAS];
	struct tdados atual;
	bool estacionado, cheio;
	char saida_menu = 'S';
	int vaga = 0;

	while (vaga < VAGAS) {
		dados[vaga].esta = false;
		vaga++;
	}

	while (saida_menu == 'S') {
		system("clear || cls");
		menu();

		printf("\nCarros estacionados:\n");
		vaga = 0;
		while (vaga < VAGAS) {
			if (dados[vaga].esta == true) {
				printf("Vaga %d: %s %.2d:%.2d %.2d/%.2d/%.4d\n", vaga+1, dados[vaga].placa, dados[vaga].hora, dados[vaga].minuto, dados[vaga].dia, dados[vaga].mes, dados[vaga].ano);
			}
			vaga++;
		}
		printf("---------\n");

		identidade(&atual);

		vaga = 0;
		estacionado = false;
		cheio = true;
		while (vaga < VAGAS) {
			if ((strcmp(atual.placa, dados[vaga].placa) == 0)&&(dados[vaga].esta == true)) {
				estacionado = true;
			}
			if (dados[vaga].esta == false) {
				cheio = false;
			}
			vaga++;
		}

		system("clear || cls");

		if (estacionado == true) {
			if (confirma("Seu carro se encontra estacionado, deseja sair? (S/N)") == 'S') {
				vaga = 0;
				while (strcmp(atual.placa, dados[vaga].placa) != 0) {
					vaga++;
				}
				dados[vaga].esta = false;
				entrada(&atual);
				cobrar(&dados[vaga], &atual, d_dias(&dados[vaga], &atual));
			}
		} else {
			if (cheio == false) {
				if (confirma("Deseja estacionar? (S/N)") == 'S') {
					entrada(&atual);

					vaga = 0;
					while (dados[vaga].esta != false) {
						vaga++;
					}
					dados[vaga].hora = atual.hora;
					dados[vaga].minuto = atual.minuto;
					dados[vaga].dia = atual.dia;
					dados[vaga].mes = atual.mes;
					dados[vaga].ano = atual.ano;
					strcpy(dados[vaga].placa, atual.placa);
					dados[vaga].esta = true;
				}
			} else {
				printf("O local est%c cheio! Volte mais tarde\n", 160);
			}
		}
		saida_menu = confirma("Deseja prosseguir? (S/N)");
	}
	printf("\n");
}
void menu () {
	printf("\a%c%c BEM VINDO AO ESTACIONAMENTO DO TADEU %c%c\n", 205, 185, 204, 205);
	printf("\nPRE%cO POR HORA\n 1%c hora: R$ 11,00\n 2%c %c 4%c hora: +R$ 9,00\n Demais horas: +R$ 6,00\n", 128, 166, 166, 133, 166);
	printf("\nPRE%cO DA DI%cRIA: R$ 46,00\n", 128, 181);
}
void identidade(struct tdados *p){
	printf("\nIDENTIFICA%c%cO\n\n", 128, 199);
	printf("Placa do seu veiculo (sem hifen): ");
	scanf("%s", &p->placa);
	fflush(stdin);
}
void entrada(struct tdados *p){
	bool errou;

	do {
		printf("ENTRADA/SA%cDA\n\n", 214);
		printf("Hora: ");
		scanf("%d", &p->hora);
		fflush(stdin);
		printf("Minuto: ");
		scanf("%d", &p->minuto);
		fflush(stdin);
		printf("Dia: ");
		scanf("%d", &p->dia);
		fflush(stdin);
		printf("Mes: ");
		scanf("%d", &p->mes);
		fflush(stdin);
		printf("Ano: ");
		scanf("%d", &p->ano);
		fflush(stdin);
		if ((p->hora < 0)||(p->hora > 24)||(p->minuto < 0)||(p->minuto > 60)) {
			if ((p->dia < 1)||(p->dia > 31)||(p->mes < 1)||(p->mes > 12)||(p->ano < 1875)||((p->mes == 2)&(p->dia > 29))) {
				errou = true;
				printf("Entrada inv%clida\n", 160);
				printf("Pressione qualquer tecla para continuar...\n");
				getchar();
				system("clear || cls");
			}
		}
	} while(errou == true);
}
int bissexto (int ano) {
	return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
}
int d_dias(struct tdados *p, struct tdados *q){
	int i_ano = p->ano, i_mes = p->mes, i_dia = p->dia, f_ano = q->ano, f_mes = q->mes, f_dia = q->dia;

	int dias_mes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

	unsigned long idias, fdias;
	unsigned long def_anos = 0;
	int i;
	int dbissexto;

	idias = i_dia;
	dbissexto = bissexto (i_ano);
	for (i = i_mes - 1; i > 0; --i){
		idias += dias_mes[dbissexto][i];
	}

	fdias = f_dia;
	dbissexto = bissexto (f_ano);
	for (i = f_mes - 1; i > 0; --i){
		fdias += dias_mes[dbissexto][i];
	}

	while (i_ano < f_ano){
		def_anos += 365 + bissexto(i_ano++);
	}

	return def_anos - idias + fdias;
}
void cobrar(struct tdados *p, struct tdados *q, int dias){
	int i_tempo = p->minuto + 60*p->hora, f_tempo = q->minuto + 60*q->hora;
	int horas, i = 1, dinheiro = 0;

	if (f_tempo > i_tempo) {
		horas = f_tempo - i_tempo;
	} else if (f_tempo < i_tempo) {
		horas = 1440 - (i_tempo - f_tempo);
		dias--;
	} else {
		horas = 0;
	}
	if (horas % 60 != 0) {
		horas /= 60;
		horas++;
	} else {
		horas /= 60;
	}
	while (horas != 0) {
		if (i == 1) {
			dinheiro += 11;
		} else if (i == 2) {
			dinheiro += 9;
		} else if (i > 4){
			dinheiro += 6;
		}
		horas--;
		i++;
	}

	dinheiro += dias*46;
	printf("O pre%co a pagar %c de R$ %d,00\n", 135, 130, dinheiro);
	printf("Agradecemos a prefer%cncia\n", 136);
}
char confirma(char message[]){
	bool erro = false;
	char i;
	do {
		erro = false;
		printf("%s\n", message);
		scanf("%c", &i);
		fflush(stdin);
		if ((i != 'S')&&(i != 'N')) {
			erro = true;
			printf("Entrada inv%clida\n\nPressione qualquer tecla para continuar...", 160);
			getchar();
			system("clear || cls");
		}
	}	while (erro == true);
	return i;
}
