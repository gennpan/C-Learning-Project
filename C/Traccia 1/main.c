// Traccia 1: Conquista del territorio
// Gennaro Panico - Mat: 0124002115
// A.A. 2020-2021



/*Si vuole sviluppare un programma per la simulazione di una fase di un gioco in cui si
scontrano 3 giocatori per la conquista del territorio.
Ogni giocatore è identificato da un Cognome e Nome. Il campo da gioco viene
considerato come una mappa regolare di dimensioni 4 x 4. Ogni giocatore
inizialmente possiede più celle, in modo tale che l’insieme di tutte le celle dei diversi
giocatori ricopre tutto il campo da gioco (in Figura le celle rosse, verdi e blue). Le
celle sono generate automaticamente e casualmente.

Il gioco procede in questo modo:
• Ad ogni turno si sceglie un attaccante e un difensore (devono avere celle
contigue).
• I due giocatori lanciano 1 dado a testa. Vince quello che ha ottenuto un
punteggio maggiore. In caso di parità vince il difensore.
• Il vincitore conquista il territorio dell’avversario. Se l’attaccante perde il
territorio passa il turno ad un altro giocatore.
• Il gioco continua finché un giocatore non conquista tutti i territori o quando
si superano 100 turni.*/



//Direttive al preprocessore
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>


//DEFINISCO UNA STRUCT PER REGISTRARE I GIOCATORI
typedef struct giocatore_strt{
unsigned	char cognome[100];
unsigned	char nome[100];
            int territori;
unsigned	int colore;
unsigned	int vincite;
}Giocatore;

Giocatore utenti[3];

//PROTOTIPI DI FUNCTION
void random(int campo[][4],int l_l,int l_n);
int partita(int campo[][4], Giocatore utenti[]);
int conta_terreni(int campo[][4], int t);
void setColor(unsigned short int);

//INSERIMENTO COLORE NEL GRAFICO DELLE VINCITE
enum ConsoleColors {
   WhiteFore   = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
   Red=      79,
   Blue=     25,
   Green=    45,
   BlackBack=0,
};

//IL MAIN
int main() {

    setColor(BlackBack);
    setColor(WhiteFore);

    // 1=ROSSO; 2=VERDE; 3=BLU.
	int campo[4][4];
	int l_l = 4, l_c = 4;
	Giocatore utenti[3];
	int i, f = 3, j, k;
	int p=0;
	int result;
	int colore = 0;


	printf("\t\t\t\t\t\t\t\t\t|____CONQUISTA DEL TERRITORIO____|\n\n");
    printf("Requisiti di Gioco: Registra 3 giocatori usando |1=ROSSO; 2=VERDE; 3=BLU| per poter giocare. Buon divertimento!!\n\n\n\n\n");

    //IMPLEMENTO LA REGISTRAZIONE DEI GIOCATORI...
	for (i = 0; i < 3; i++) {                     //...CICLO FOR CON VARIABILE DI CICLO(i) PER REGISTRARE I GIOCATORI
		int c_temp = 0, end = 0;
		printf("Inserisci Carlo Rosario che puzza %i : ", i + 1);
				fflush(stdin);
		//gets(utenti[i].cognome);
		scanf("%s", utenti[i].cognome);
		fflush(stdin);
		printf("Inserire il nome del Giocatore %i : ", i + 1);
		scanf(" %s", utenti[i].nome);
		fflush(stdin);
		printf("\n");
		do {
			printf("Inserire il colore del Giocatore %i : ", i + 1);
			fflush(stdin);
			scanf("%i", &utenti[i].colore);
			printf("E' stato scelto il colore numero %i \n", utenti[i].colore);
			if (
				i == 1 && utenti[i].colore == utenti[i - 1].colore || i == 2 && utenti[i].colore == utenti[i - 2].colore)
				 {
				printf("Il colore e' gia' stato scelto, scegli un altro colore! \n");
				k = 0;
			}
			else {
				k = 4;
			}
		} while (k < 3);

		utenti[i].vincite = 0;
		printf("|-------------------------------------------------|\n");
		printf("|____________Giocatore %i creato!__________________|\n", i + 1);
		printf("|-------------------------------------------------|\n\n\n\n\n");
		fflush(stdin);
	}




	random(campo, l_l, l_c);        //CAMPO RANDOMICO

	for (i = 0; i < 4; i++) {       //STAMPA DEL TEERRITORIO DI GIOCO
		printf("              ");
		for (j = 0; j < 4; j++) {

			if (campo[j][i] == 3) {
                setColor(Green);
				printf("  ");
				setColor(Green);
			}

			if (campo[j][i] == 2) {
			    setColor(Blue);
				printf("  ");
				setColor(Blue);
			}
			if (campo[j][i] == 1) {
                setColor(Red);
				printf("  ");
                setColor(Red);
                }
            }
    setColor(BlackBack);
    setColor(WhiteFore);
        printf(" ");
		printf("\n");
    }

	//ESITI DI PARITITA
	do{
		p++;
		result = partita(campo, utenti);
		if (result == 1) {
			utenti[0].vincite++;
		}
		else if (result == 2) {
			utenti[1].vincite++;
		}
		else if (result == 3) {
			utenti[2].vincite++;
			}

	}while (p <= 99);


    //GESTIONE STAMPA CLASSIFICA
	printf("\n\n\nClassifica Vittorie dopo 100 partite giocate. \n");
	if (utenti[0].vincite > utenti[1].vincite&& utenti[0].vincite > utenti[2].vincite)
        {
		printf("Prima Posizione:  Giocatore 1 \n");
		if (utenti[1].vincite > utenti[2].vincite)
		{
            printf("Seconda Posizione:  Giocatore 2 \n");
			printf("Terza Posizione:  Giocatore 3 \n");
		}else if (utenti[1].vincite < utenti[2].vincite){
			printf("Seconda Posizione:  Giocatore 3 \n");
			printf("Terza Posizione:  Giocatore 2 \n");
		}else if (utenti[1].vincite == utenti[2].vincite){
			printf("Seconda Posizione:  Giocatore 2 \n");
			printf("Terza Posizione:  Giocatore 3 \n");
		   }
	    }

    if (utenti[1].vincite > utenti[2].vincite&& utenti[1].vincite > utenti[0].vincite)
        {
		printf("Prima Posizione:  Giocatore 2 \n");
		if (utenti[0].vincite > utenti[2].vincite) {
			printf("Seconda Posizione:  Giocatore 1 \n");
			printf("Terza Posizione:  Giocatore 3 \n");
		}else if (utenti[0].vincite < utenti[2].vincite) {
			printf("Seconda Posizione:  Giocatore 3 \n");
			printf("Terza Posizione:  Giocatore 1 \n");
		}else if (utenti[0].vincite == utenti[2].vincite) {
			printf("Seconda Posizione:  Giocatore 3 \n");
			printf("Terza Posizione:  Giocatore 1 \n");
		  }
        }

	if (utenti[2].vincite > utenti[0].vincite&& utenti[2].vincite > utenti[1].vincite)
        {
		printf("Prima Posizione:  Giocatore 3 \n");
		if (utenti[0].vincite > utenti[1].vincite){
			printf("Seconda Posizione:  Giocatore 1 \n");
			printf("Terza Posizione:  Giocatore 2 \n");
		}
		else if (utenti[0].vincite < utenti[1].vincite){
			printf("Seconda Posizione:  Giocatore 2 \n");
			printf("Terza Posizione:  Giocatore 1 \n");
		}
		else if (utenti[0].vincite == utenti[1].vincite){
			printf("Seconda Posizione:  Giocatore 1 \n");
			printf("Terza Posizione:  Giocatore 2 \n");
		  }
	    }

	return 0;
}

void setColor(unsigned short int color){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}


//DEFINIZIONE DI FUNCTION
//Function per generare il campo in modo randomico.
void random(int campo[][4], int l_l, int l_n){
	srand(time(NULL));

	int i, j;
	int r = 0, g = 0, v = 0;
	int temp, esc;

	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			do {
				esc = 0;
				temp = 1 + rand() % 3;
				if (temp == 1 && r <= 5){
                        campo[i][j] = 1;
						r++;
						esc = 2;
				    }
				else if (temp == 2 && g <= 5){
					campo[i][j] = 2;
					g++;
					esc = 2;
				}
				else if (temp == 3 && v <= 5){
					campo[i][j] = 3;
					v++;
					esc = 2;
				}
			} while (esc < 1);
		}
	}

}

//Function di simulazione partita.
int partita(int campo[][4], Giocatore utenti[]) {
	int a = 0, d, r = 0, r_a = 0, r_b = 0, turni_partita = 1;
	int a_c = 0, a_r = 0, d_c = 0, d_r = 0;
	int da, dd, dr = 0, vincita= 0;
	int match = 0;
	int t;

	srand(time(NULL));




	do {                                                        //Conteggio dei territori che possiede il giocatore ad ogni turno.
		for (t = 0; t < 3; t++) {
			utenti[t].territori = conta_terreni(campo, t);
		}

			do {                                                //Attaccante e difensori randomici con rand.
				if (a == 0){
					a = 1 + rand() % 3;
					if (utenti[a - 1].territori > 0)
						r_a = 2;
					else {
						r_a = 1;
					}
				}
				else r_a = 2;
			} while (r_a < 1);

			do {
				d = 1 + rand() % 3;
				d_r = rand() % 3;
				d_c = rand() % 3;
				if (d != a && utenti[d - 1].territori > 0 && campo[d_r][d_c] == d){

				if (campo[d_r][d_c + 1] == a){
					a_r = d_r;
					a_c = d_c + 1;
					r_b = 2;
				}
				else if (campo[d_r][d_c - 1] == a){
					a_r = d_r;
					a_c = d_c - 1;
					r_b = 2;
				}
				else if (campo[d_r + 1][d_c] == a){
					a_r = d_r + 1;
					a_c = d_c;
					r_b = 2;
				}
				else if (campo[d_r - 1][d_c] == a){
					a_r = d_r - 1;
					a_c = d_c;
					r_b = 2;

				}
				else r_b = 0;
			}

			} while (r_b < 1);

            //Simulazione dei dati di gioco, vittoria o sconfitta del giocatore.
			do {
				da = 1 + rand() % 6;
				dd = 1 + rand() % 6;
				if (da > dd) {
					campo[d_r][d_c] = utenti[a-1].colore;
					dr = 2;
				}
				else {
					if (da < dd|| da == dd){
						a = 0, dr = 2;
					}
				}
			} while (dr < 1);

			turni_partita++;


			if (utenti[0].territori < 1 && utenti[1].territori < 1){
				match = 2;
			}
			else if (utenti[0].territori < 1 && utenti[2].territori < 1){
				match = 2;
			}
			else if (utenti[1].territori < 1 && utenti[2].territori < 1){
				match = 2;
			}

			if (turni_partita > 99){
				match = 4;
			}

	}while(match <1);


    //Gestione per la determinazione della vincita dopo i 99 turni di gioco.
	if (turni_partita > 99) {
			if (utenti[0].territori > utenti[1].territori && utenti[0].territori > utenti[2].territori){
				vincita = 1;
			}

			else if (utenti[1].territori > utenti[0].territori && utenti[1].territori > utenti[2].territori)
			{
				vincita = 2;
			}

			else if (utenti[2].territori > utenti[0].territori && utenti[2].territori > utenti[1].territori){
				vincita = 3;
			}
		}

	if (utenti[1].territori == 0 && utenti[2].territori == 0){
		vincita = 1;
	}

	else if (utenti[1].territori == 0 && utenti[3].territori == 0){
		vincita = 2;

	}

	if (utenti[2].territori == 0 && utenti[3].territori == 0){
		vincita = 3;

	}

	return vincita;
}

//Function per conteggio territori.
int conta_terreni(int campo[][4], int t){
	int i,j, terreni=0, t_u=0;
	t_u = t + 1;
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				if (campo[i][j] == t_u)
					terreni++;
			}
		}
		return terreni;
}
