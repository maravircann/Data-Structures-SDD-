#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* nrPagini;
	char* titlu;
	float pret;
}carte;

typedef struct {
	carte info;
	struct nodLS* next;
}nodLS;

nodLS* initializareNod(carte c) { //o folosim in inserare cand vrem sa adaugam nod in lista
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->info.nrPagini = (int*)malloc(sizeof(int));
	*(nou->info.nrPagini) = *(c.nrPagini);

	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);

	nou->info.pret = c.pret;

	nou->next = NULL;
	return nou;
}

//met 1 returneaza o valoare noua (*)
nodLS* inserareNod1(nodLS* capLS, carte c) {
	nodLS* nou = initializareNod(c);

	if (capLS == NULL) {
		capLS = nou;
	}
	else {
		//creare nod temporar pentru a parcurge lista
		nodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou; //leaga utl nod de nodul adaugat
	}

	return capLS;
}



//met 2 modifica direct pointerul in functie (**)

void inserareNod2(nodLS** capLS, carte c) {
	nodLS* nou = initializareNod(c);

	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {
		nodLS* temp = *capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

//temp != NULL daca vrem sa procesam toate nodurile din lista
//temp-> != NULL daca vrem sa ne oprim pe penultimul nod
void traversareLista(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) { //vrem sa parcurgem toate nodurile
		printf("\ntitlu=%s, numarPagini=%d, pret=%5.2f", temp->info.titlu, *(temp->info.nrPagini), temp->info.pret);
		temp = temp->next;
	}
}


void dezalocareLista(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->info.nrPagini);
		free(temp->info.titlu);
		free(temp);
		temp = aux;
	}
}

void salvareCartiVector(nodLS* capLS, carte* vector, int* nrElem, float prag){
	nodLS* temp = capLS;
	while (temp != NULL) {
		if (temp->info.pret >= prag) {
			vector[*nrElem].nrPagini = (int*)malloc(sizeof(int));
			*(vector[*nrElem].nrPagini) = *(temp->info.nrPagini);

			vector[*nrElem].titlu = (char*)malloc((strlen(temp->info.titlu)+1)*sizeof(char));
			strcpy(vector[*nrElem].titlu, temp->info.titlu);

			vector[*nrElem].pret = temp->info.pret;
			(*nrElem)++;
		}
		temp = temp->next;
	}
}

void main() {
	int nrCarti;
	carte c;
	nodLS* capLS = NULL;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		c.nrPagini = (int*)malloc(sizeof(int));
		fscanf(f, "%d", c.nrPagini);

		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);

		fscanf(f, "%f", &c.pret);

		//capLS = inserareNod1(capLS, c);
		inserareNod2(&capLS, c);
		free(c.nrPagini);
		free(c.titlu);
	}
	fclose(f);

	traversareLista(capLS);


	printf("\n-------------Vector--------------\n");

	carte* vect = (carte*)malloc(nrCarti * sizeof(carte));
	int nrElem = 0;
	salvareCartiVector(capLS, vect, &nrElem, 10.0f);
	for (int i = 0; i < nrElem; i++) {
		printf("\ntitlu = %s, nrPag = %d, Pret = %5.2f", vect[i].titlu, *(vect[i].nrPagini), vect[i].pret);
	}
	for (int i = 0; i < nrElem; i++) {
		free(vect[i].nrPagini);
		free(vect[i].titlu);
	}
	free(vect);
	dezalocareLista(capLS);
}