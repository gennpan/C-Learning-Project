// Traccia 2: Archivio telefonico
// Gennaro Panico - Mat: 0124002115
// A.A. 2020-2021

/*Si vuole simulare l’archivio di chiamate di un gestore telefonico. L’archivio risulta
mensile (31 giorni) . Ogni giorno vengono effettuate al massimo 10 chiamate e il
costo al minuto di una chiamata è di 10 centesimi. Ogni chiamata è identificata dal
numero chiamante, il numero ricevente, la durata della chiamata. Provvedere
all’implementazione dell’algoritmo per la simulazione dell’archivio.
Permettere, inoltre, all’utente di
• Dato un numero telefonico visualizzare tutte le chiamate con le relative
informazioni in un singolo giorno
• Dato un giorno e un numero telefonico visualizzare il costo totale delle
chiamate.
L’archivio può anche essere inizializzato con informazioni casuali.*/



//Direttive di preprocessore
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define CALLS 10                //definisco le costanti cosicchè mi basterà cambiare valore quì per cambiarlo in tutto il file main.c.
#define DAYS 30




char *numeri[]= {"3332445930", "338127698", "3289064985", "3285245381", "3331099740"};



//Dichiarazione struct con dati delle chiamate.
typedef struct
{
    char *chiamante;
    int ricevente;
    int durata;
} Dati;


//Definisco una struct contenente l'archivio mensile.
typedef struct
{
    Dati elenco[CALLS][DAYS];
} Archivio;


//Function per creare l'archivio, essa restituisce una struct di tipo Archivio.
Archivio creaDati()
{
    int i=0, j=0, k=0;
        Archivio archivio;


            for (i=0; i<DAYS; i++){
                for (k=0; k<CALLS; k++){
                    archivio.elenco[k][i].chiamante=malloc(sizeof(Dati));
                    j=rand()%5;
                    strcpy(archivio.elenco[k][i].chiamante, numeri[j]);
                    archivio.elenco[k][i].ricevente = 1000000+rand()%999999+1;
                    archivio.elenco[k][i].durata = rand()%121;
                    }
                  }
return archivio; //la function ritorna l'archivio...
}


//Procedura per la stampa dell'archivio, prende in input la struct di tipo Archivio.
void stampaDati(Archivio archivio)
{
    int costo=0;
    int i=0, k=0;
    for (i=0; i<=DAYS;){
        printf("\n\n\t\t----------[GIORNO %d]----------\n\n CHIAMANTE\t\tRICEVENTE\t\tDURATA\t\tCOSTO", i+1);
        for (k=0; k<CALLS; k++){
            costo=0.10*archivio.elenco[k][i].durata;
            printf("\n[C.%d] %s\t%d\t\t\t%d\tmin. \t%i\euro", k+1, archivio.elenco[k][i].chiamante, archivio.elenco[k][i].ricevente, archivio.elenco[k][i].durata, costo);
            }
    printf("\n\n\t\tPremi INVIO per verificare i successivi giorni dell'elenco.\n\n\t\t\t\t Premi 'x' per ritornare.\n");
    getchar();
    if (getchar()=='x')
        break;
        else
    i++; //incremento la variabile contatore del primo ciclo for, quello più esterno.
    }
}


//Procedura per la stampa dell'elenco dei numeri telefonici.
void stampaElenco()
{
    int i=0;
    printf("I numeri presenti attualmente nel database (ita) sono i seguenti:\n\n");
    for (i=0; i<5; i++)
    printf("[N%d] (+39)%s\n", i+1, numeri[i]);
    getchar();
}







//IL MAIN
int main()
{
    srand(time(NULL));


    Archivio simula;
    stampaElenco();
    simula = creaDati();
    stampaDati(simula);

    return 0;
}

