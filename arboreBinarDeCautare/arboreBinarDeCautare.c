#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* titlu;
	int nrAutori;
	float pret;
}carte;

typedef struct {
	carte info;
	struct nodArb* stanga, * dreapta;
}nodArb;


nodArb* creareNod(carte c, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.nrAutori = c.nrAutori;
	nou->info.pret = c.pret;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;

}

nodArb* inserareNod(nodArb* rad, carte c) {
	if (rad != NULL) {
		if (c.cod < rad->info.cod) {
			rad->stanga=inserareNod(rad->stanga, c);
			return rad;
		}
		else if (c.cod > rad->info.cod) {
			rad->dreapta=inserareNod(rad->dreapta, c);
			return rad;
		}
		else {
			return rad;
		}
	}
	creareNod(c, NULL, NULL);
}

void preordine(nodArb* rad) {
	if (rad != NULL) {
		printf("\ncod: %d, titlu: %s, nrAutori: %d, pret: %5.2f", rad->info.cod, rad->info.titlu, rad->info.nrAutori, rad->info.pret);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.titlu);
		free(rad);
	}
}

int maxim(int a, int b) {
	int maxim = a;
	if (maxim < b) {
		maxim = b;
	}
	return maxim;
}

int inaltimeArbore(nodArb* rad) {
	if (rad != NULL) {
		return 1 + maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta));
	}
	else {
		return 0;
	}
}

void salvareVector(nodArb* rad, carte* vector, int* nr, int prag) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL && rad->info.pret > prag) {
			vector[*nr].cod = rad->info.cod;
			vector[*nr].titlu = (char*)malloc((strlen(rad->info.titlu) + 1) * sizeof(char));
			strcpy(vector[*nr].titlu, rad->info.titlu);
			vector[*nr].nrAutori = rad->info.nrAutori;
			vector[*nr].pret = rad->info.pret;

			(*nr)++;
		}
		salvareVector(rad->stanga, vector, nr, prag);
		salvareVector(rad->dreapta, vector, nr, prag);

	}
}
void main() {
	int nrCarti;
	char buffer[20];
	carte c;
	nodArb* rad = NULL;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		fscanf(f, "%d", &c.nrAutori);
		fscanf(f, "%f", &c.pret);

		rad = inserareNod(rad, c);
	}
	fclose(f);

	preordine(rad);
	int nr = 0;
	carte* vector = (carte*)malloc(sizeof(carte) * nrCarti);
	salvareVector(rad, vector, &nr, 100);

	for (int i = 0; i < nr; i++) {
		printf("\n %d, %s, %d, %5.2f", vector[i].cod, vector[i].titlu, vector[i].nrAutori, vector[i].pret);
	}
	dezalocare(rad);
}