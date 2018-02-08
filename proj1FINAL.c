/* ========================================================================== */
/* ======================= Instituto Superior Tecnico ======================= */
/* ======================= PROJETO 1 - IAED 2015/2016 ======================= */
/* ============= Mariana Mendes, 83521 | Miguel Regouga, 83530 ============== */
/* ============================== GRUPO AL009 =============================== */
/* ========================================================================== */



/* ========================================================================== */
/* =============================== BILBIOTECAS ============================== */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/* ========================================================================== */
/* =============================== CONSTANTES =============================== */
/* ========================================================================== */

#define AIRPORT_CODE 3
#define ABERTO       1
#define FECHADO      0
#define CAPACIDADE   1000



/* ========================================================================== */
/* =============================== ESTRUTURAS =============================== */
/* ========================================================================== */


/* ========================= ESTRUTURA DO AEROPORTO ========================= */

typedef struct {

char ident[AIRPORT_CODE + 1];
long capacidade;
int  estado;

} airport;



/* ======================== ESTRUTURA DO BUBBLESORT ========================= */

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)



/* ========================================================================== */
/* -=============================== PROTOTIPOS ============================== */
/* ========================================================================== */

void add_airport (char id[], int capacidade);                    /* COMANDO A */
void max_airport (char id[], int capacidade);                    /* COMANDO I */
void add_flight (char id1[], char id2[]);                        /* COMANDO F */
void add_route (char id1[], char id2[]);                         /* COMANDO G */
void remove_flight (char id1[], char id2[]);                     /* COMANDO R */
void remove_route (char id1[], char id2[]);                      /* COMANDO S */
void num_flights (char id1[], char id2[]);                       /* COMANDO N */
void airport_max_flights( );                                     /* COMANDO P */
void airport_max_connections( );                                 /* COMANDO Q */
void popular_flights( );                                         /* COMANDO V */
void shutdown_airport( char id[] );                              /* COMANDO C */
void reopen_airport(char id[]);                                  /* COMANDO O */
void list(int type);                                             /* COMANDO L */
int search_airports(char id1[]);            					 /* FAUXILIAR */
int search_airport_define(char id[]);            				 /* FAUXILIAR */
int noutgoing ( int i );										 /* FAUXILIAR */
int nincoming ( int i );	 									 /* FAUXILIAR */
void bubble(Item a[], int l, int r);	 						 /* FAUXILIAR */



/* ========================================================================== */
/* =========================== VARIAVEIS GLOBAIS ============================ */
/* ========================================================================== */

airport airports[CAPACIDADE]; 				 /* Vetor com todos os aeroportos */
int cont_air = 0; 							/* Numero de aeroportos inseridos */
int voos[CAPACIDADE][CAPACIDADE];       /* Matriz de voos incoming e outgoing */
int cont_voos = 0;                                /* Numero de voos inseridos */



/* ========================================================================== */
/* =========================== FUNCOES AUXILIARES =========================== */
/* ========================================================================== */


/* ============================ SEARCH AIRPORTS ============================= */
/* 		Devolve o indice do aeroporto, se estiver aberto e definido 		  */

int search_airports(char id[]) {

	int i = 0;
	for(i = 0; i <= CAPACIDADE; i++) {
		
		if ((strcmp(airports[i].ident, id) == 0) && (airports[i].estado == ABERTO)) {
			return i;
		}
	
	}

	return 1000;
}



/* ======================== SEARCH AIRPORTS DEFINE ========================== */
/* 			Devolve o indice do aeroporto, se estiver apenas definido  		  */

int search_airport_define(char id[]) {

	int i = 0;
	for(i = 0; i <= CAPACIDADE; i++) {
		
		if (strcmp(airports[i].ident, id) == 0) 
			return i;
	}

	return 1000;
}



/* ============================== N OUTGOING ================================ */
/* 					Devolve o numero de voos outgoing (partidas)  			  */

int noutgoing ( int i ){
	
	int j, cont = 0;
	for ( j = 0; j < CAPACIDADE; j++){
		cont += voos[i][j];
	}
	return cont;
}



/* ============================== N INCOMING ================================ */
/* 					Devolve o numero de voos incoming (chegadas)			  */

int nincoming ( int i ){
	
	int j, cont = 0;
	for ( j = 0; j < CAPACIDADE; j++){
		cont += voos[j][i];
	}
	return cont;
}



/* ============================= BUBBLE SORT ================================ */
/*							Algoritmo de ordenacao							  */

void bubble(Item a[], int l, int r) {
	 int i, j;
	  for (i = l; i < r; i++)
	     for (j = l; j < r-i; j++)
    	    compexch(a[j], a[j+1]);
}



/* ========================================================================== */
/* ================================== MAIN ================================== */
/* ========================================================================== */

int main (){

	int c, capacidade, d;
	char id[4], id1[4], id2[4];
	
	while ((c = getchar())){
		switch (c) {

			case 'A':
				scanf("%s %d", id, &capacidade);
				add_airport(id, capacidade);
				break;

			case 'I':
				scanf ("%s%d", id, &capacidade);
				max_airport (id, capacidade);
				break;

			case 'F':
				scanf ("%s%s", id1, id2);
				add_flight (id1, id2);
				break;

			case 'G':
				scanf ("%s%s", id1, id2);
				add_route (id1, id2);
				break;  

			case 'R':
				scanf ("%s%s", id1, id2);
				remove_flight (id1, id2);
				break;

			case 'S':
				scanf ("%s%s", id1, id2);
				remove_route (id1, id2);
				break;

			case 'N':
				scanf ("%s%s", id1, id2);
				num_flights (id1, id2); 
				break;

			case 'P':
				airport_max_flights( );
				break;

			case 'Q':
				airport_max_connections( );
				break;

			case 'V':
				popular_flights( );
				break;

			case 'C':
				scanf ("%s", id);
				shutdown_airport( id );
				break;

			case 'O':
				scanf ("%s", id);
				reopen_airport( id ); 
				break;

			case 'L':
				scanf ("%d", &d);
				list(d); 
				break;
			
			case 'X':
				printf("%d:%d\n", cont_voos, cont_air);
				exit(0);
		}
	}

	return 0;
}



/* ========================================================================== */
/* ================================ COMANDOS ================================ */
/* ========================================================================== */


/* =============================== COMANDO A ================================ */
/* 							Adiciona um novo aeroporto						  */

void add_airport (char id[], int capacidade)   {

	airport new_airport;
	strcpy (new_airport.ident, id);
	new_airport.capacidade = capacidade;
	new_airport.estado = ABERTO;
	
	airports[cont_air] = new_airport;
	cont_air++; 					   /* Incrementa o contador de aeroportos */

}



/* =============================== COMANDO I ================================ */
/* 					Altera a capacidade maxima de um aeroporto				  */

 void max_airport (char id[], int capacidade) {
	
	int i = 0, ctotal = 0, incoming, outgoing;
	char nome[4];
	strcpy(nome, id);

	for(i = 0; i <= CAPACIDADE; i++) {
		
		if ((strcmp(airports[i].ident, nome) == 0) && (airports[i].estado == ABERTO)) {
			/* Verifica se o ID introduzido esta no sistema, e se o aeroporto correspondente esta aberto */
			incoming = nincoming( i );
			outgoing = noutgoing( i );
			ctotal = incoming + outgoing;
			if (airports[i].capacidade + capacidade >= ctotal){
				/* Verifica se a nova capacidade maxima e superior ou igual ao numero de voos atual do aeroporto */
				airports[i].capacidade += capacidade;
				return;
			}
		}
		ctotal = 0;
	}
	printf( "*Capacidade de %s inalterada\n", nome);	
} 



/* ================================ COMANDO F =============================== */
/* 			Adiciona os voos de ida e volta entre os aeroportos indicados	  */

void add_flight (char id1[], char id2[]) {

	int partida, chegada, atual1, atual2;
	partida = search_airports(id1);
	chegada = search_airports(id2);
	
	if (partida != 1000 && chegada != 1000) { /* Verifica se o aeroporto esta definido e aberto */ 
		atual1 = (nincoming(partida) + noutgoing(partida));
		atual2 = (nincoming(chegada) + noutgoing(chegada));
		
		/* 	As COLUNAS correspondem as chegadas (os voos que entram no respetivo 
		aeroporto). As LINHAS correspondem as partidas (os voos que saem do 
		respetivo aeroporto).*/
		
		if ((atual1 + 2 <= airports[partida].capacidade) && (atual2 + 2 <= airports[chegada].capacidade)) {
		/* Verifica se e possivel adicionar os voos consoante a capacidade maxima dos aeroportos */
		
		/* Adiciona o voo de ida */
		voos[partida][chegada] += 1;
	
		/* Adiciona o voo de volta */
		voos[chegada][partida] += 1;
	
		cont_voos += 2; /* Adiciona 2 voos ao contador de voos, o de ida e volta */
		}
		
		else printf( "*Impossivel adicionar voo RT %s %s\n", id1, id2);
		
	}

	else {
		printf( "*Impossivel adicionar voo RT %s %s\n", id1, id2);
	}
}



/* ================================ COMANDO G =============================== */
/* 			Adiciona um voo de ida com partida em ID1 e chegada em ID2		  */

void add_route (char id1[], char id2[]) {
	
	int partida, chegada, atual1, atual2;
	partida = search_airports(id1);
	chegada = search_airports(id2);
		if (partida != 1000 && chegada != 1000 ) {
			atual1 = (nincoming(partida) + noutgoing(partida));
			atual2 = (nincoming(chegada) + noutgoing(chegada));
			if ((atual1 + 1 <= airports[partida].capacidade) && (atual2 + 1 <= airports[chegada].capacidade)){
				/* Adiciona voo de ida */
				voos[partida][chegada] += 1;
				cont_voos += 1;
			}
			else
				printf( "*Impossivel adicionar voo %s %s\n", id1, id2);
	
		
	}
		else
			printf( "*Impossivel adicionar voo %s %s\n", id1, id2);
}



/* ================================ COMANDO R =============================== */
/* 			Remove o voo de ida com partida em ID1 e chegada em ID2			  */


void remove_flight (char id1[], char id2[]) {
	
	int partida, chegada;
	
	partida = search_airports(id1);
	chegada = search_airports(id2);
	
	if (partida != 1000 && chegada != 1000 && voos[partida][chegada] > 0) {
		/* Verifica se  os aeroportos estao definidos e se possivel remover um voo */
		
	 	voos[partida][chegada] -= 1;
		cont_voos -= 1; 				  /* Remove 1 voo do contador de voos */
	}

	else {
		printf( "*Impossivel remover voo %s %s\n", id1, id2);
	}
}



/* ================================ COMANDO S =============================== */
/* 		Remove o voo de ida e volta com partida em ID1 e chegada em ID2		  */

void remove_route (char id1[], char id2[]) {
	
	int partida, chegada;
	partida = search_airports(id1);
	chegada = search_airports(id2);
	
	if (partida != 1000 && chegada != 1000 && voos[partida][chegada] > 0 && voos[chegada][partida] > 0 ) {
		voos[partida][chegada] -= 1;
		voos[chegada][partida] -= 1;
		cont_voos -= 2;
	}

	else {
		printf( "*Impossivel remover voo RT %s %s\n", id1, id2);
	}

}



/* ================================ COMANDO N =============================== */
/* 			Retorna o numero de voos entre os aeroportos ID1 e ID			  */

void num_flights (char id1[], char id2[]) {
	
	int partida, chegada;
	partida = search_airport_define(id1);
	chegada = search_airport_define(id2);
	
	if (partida == 1000) {
		printf( "*Aeroporto %s inexistente\n", id1);
	}
	if (chegada == 1000){
		printf( "*Aeroporto %s inexistente\n", id2);
	}
			
	if (partida != 1000 && chegada != 1000)
		printf("Voos entre cidades %s:%s:%d:%d\n", id1, id2, voos[partida][chegada], voos[chegada][partida]);
		
	else
		return;
}



/* ================================ COMANDO P =============================== */
/* 			Retorna o aeroporto com o maior numero total de voos			  */

void airport_max_flights( ) {
	
	int i, max_voos[CAPACIDADE], max = 0, aero = 0, partidas, chegadas, soma;
	
	for (i = 0; i < cont_air; i++) {
		partidas = noutgoing(i);
		chegadas = nincoming(i);
		soma = partidas + chegadas;
		max_voos[i] = soma;
		
		/* Apenas guarda se o max for superior, pois se nao for superior e for igual, 
		aquele que foi encontrado primeiro é aquele que está no sistema a mais tempo,
		pois o indice é mais pequeno */
		
		if (max < max_voos[i]) {
			max = max_voos[i];
			aero = i;
		}
	}
	
	printf("Aeroporto com mais rotas %s:%d:%d\n", airports[aero].ident, noutgoing(aero), nincoming(aero));
}



/* ========================================================================== */
/* ================================ COMANDO Q =============================== */
/* ========================================================================== */

void airport_max_connections( ) {
	
	int i, j, k, conects[CAPACIDADE], max = 0, aero = 0;
	
	for (k = 0; k < cont_air; k++) {
		conects[k] = 0;
	}
	
	for (i = 0; i < cont_air; i++) {
		for (j = 0; j < cont_air; j++) {
			if (voos[i][j] > 0 || voos[j][i] > 0) {
				conects[i]++;
			}
		}
		
		if (max < conects[i]) {
		max = conects[i];
		aero = i;
		}
	}
	
	printf("Aeroporto com mais ligacoes %s:%d\n", airports[aero].ident, conects[aero]);
	
}




/* ================================ COMANDO V =============================== */
/* 	Retorna o par de aeroportos com maior numero de voos de ID1 para ID2	  */

void popular_flights( ) {
	
	int i, j, max_i = 0, max_j = 0, max = 0;
	
	for (i = 0; i < cont_air; i++) {
		for (j = 0; j < cont_air; j++) {
			
			if (voos[i][j] > max) {
				max = voos[i][j];
				max_i = i;
				max_j = j;
			}
		}
	}
	
	printf("Voo mais popular %s:%s:%d\n", airports[max_i].ident, airports[max_j].ident, max);
}



/* ================================ COMANDO C =============================== */
/* 					Encerra o aeroporto atualmente em operacao		  		  */

void shutdown_airport( char id[] ){
	
	int i, j;
	char nome[4];
	strcpy(nome, id);

	for(i = 0; i <= CAPACIDADE; i++) {
		
		if (strcmp(airports[i].ident, nome) == 0) {
			
			airports[i].estado = FECHADO;
			for ( j = 0; j < CAPACIDADE; j++){
				cont_voos -= (voos[i][j] + voos[j][i]);
				voos[i][j] = 0;
				voos[j][i] = 0;
				
			}
			
			return;
		}

	}

	printf( "*Aeroporto %s inexistente\n", nome);	
}
	


/* ================================ COMANDO O =============================== */
/* 					Reabre o aeroporto atualmente encerrado 		  		  */

void reopen_airport(char id[]){
	
	int i = 0;
	char nome[4];
	strcpy(nome, id);

	for(i = 0; i <= CAPACIDADE; i++) {
		
		if (strcmp(airports[i].ident, nome) == 0) {
			
			airports[i].estado = ABERTO;
			return;
		}

	}
	printf( "*Aeroporto %s inexistente", nome);	
}



/* ================================ COMANDO L =============================== */
/* Emite listagem de aeroportos e voos de acordo com o numero inserido (0/1/2)*/

void list(int type){
	
	int i;
	char nome[4];

	if (type == 0){
	/* L 0: imprime a lista de aeroportos ordenados pela ordem de inserecao no sistema */
	
		for(i = 0; i < cont_air; i++){
			printf("%s:%ld:%d:%d\n", airports[i].ident, airports[i].capacidade, noutgoing(i), nincoming(i) );
		}	
	}
	
	
	else if (type == 1){
	/* L 1: imprime a lista de aeroportos ordenados por ordem alfabetica */
		
		int i, j, k = 0;
  		airport alfabetico[CAPACIDADE], aux;
		
		for (i = 0; i < cont_air; i++){
			alfabetico[i] = airports[i];
		}
		
		for (i = 1; i < cont_air; i++) {
    		for (j = 1; j < cont_air; j++, k++) {

        		if (strcmp(alfabetico[j - 1].ident, alfabetico[j].ident) > 0) {
        			/* compara se o id do aeroporto anterior é maior que o atual, alfabeticamente */ 
        			/* se sim irá inverte-los colocando o maior, alfabeticamente, na posição atual */
        			aux = alfabetico[j - 1];
        	    	alfabetico[j - 1] = alfabetico[j];
        		 	alfabetico[j] = aux;
            	}
      		}
   		}
		for(i = 0; i < cont_air; i++){
			strcpy(nome, alfabetico[i].ident);
			for( j = 0; j < cont_air; j++){
				if (strcmp( alfabetico[i].ident, airports[j].ident) == 0){
					k = j;
				}
			}
			printf("%s:%ld:%d:%d\n", nome, alfabetico[i].capacidade, noutgoing(k), nincoming(k));
		}
	}
	
	
	else if (type == 2){
		/* L 2: emite a quantidade de aeroportos com x voos */
		
		int i, j, k, voos_aeros[cont_air +1], soma_voos = 0, anterior = 0, count = 1;
		
		for (k = 0; k < cont_air +1; k++) {
			voos_aeros[k] = 0;
		}
		
		for (i = 0; i < cont_air +1; i++) {\
			/* Adiciona a um vetor a soma dos voos incoming e outcoming de um aeroporto */ 
			soma_voos = nincoming(i) + noutgoing(i);
			voos_aeros[i] += soma_voos;
		}


		
		bubble(voos_aeros, 0, cont_air);

		/* Ordena, utilizando o algoritmo de ordenacao bubble sort,
		o vetor com a soma dos voos de cada aeroporto, de modo a tornar-se mais
		facil a contagem do numero de aeroportos com a respetiva quantidade de voos */

		anterior = voos_aeros[0];
		count = 0;

		for (j = 1; j < cont_air + 1; j++) {
			if (voos_aeros[j] == anterior) count++;
			else {
				if (count != 0) {
					printf("%d:%d\n", anterior, count);
				}

				/* Caso se verifique que existem 0 aeroportos com x voos, nao e
				apresentada nenhuma resposta */

				anterior = voos_aeros[j];
    			count = 1;
			}
		}

		printf("%d:%d\n", anterior, count);
		
		}
	}
