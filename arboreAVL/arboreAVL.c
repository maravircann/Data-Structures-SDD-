#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* titlu;
	int nrAutori;
	float pret;
}carte;

typedef struct {
	int BF;
	carte info;
	struct nodAVL* stanga, * dreapta;
}nodAVL;

nodAVL* creareNod(carte c, nodAVL* st, nodAVL* dr) {
	nodAVL* nou = (nodAVL*)malloc(sizeof(nodAVL));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.nrAutori = c.nrAutori;
	nou->info.pret = c.pret;

	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}


nodAVL* inserareNod(nodAVL* rad, carte c) {
	if (rad != NULL) {
		if (c.cod < rad->info.cod) {
			rad->stanga = inserareNod(rad->stanga, c);
			return rad;
		}
		else if (c.cod > rad->info.cod) {
			rad->dreapta = inserareNod(rad->dreapta, c);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		rad = creareNod(c, NULL, NULL);
	}
}


void preordine(nodAVL* rad) {
	if (rad != NULL) {
		printf("\n cod: %d, titlu: %s, nrAutori: %d, pret: %5.2f", rad->info.cod, rad->info.titlu, rad->info.nrAutori, rad->info.pret);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void dezalocare(nodAVL* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.titlu);
		free(rad);
		
	}
}

int maxim(int x, int y) {
	int maxim = x;
	if (maxim < y) {
		maxim = y;
	}
	return maxim;
}

int inaltimeArbore(nodAVL* rad) {
	if (rad != NULL) {
		return 1 + maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta));
	}
	else {
		return 0;
	}
}

void calculBF(nodAVL* rad) {
	if(rad!=NULL){
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodAVL* rotatieDreapta(nodAVL* rad) {
	if (rad != NULL) {
		nodAVL* nod1 = rad->stanga;
		rad->stanga = nod1->dreapta;
		nod1->dreapta = rad;
		rad = nod1;
		return rad;
	}
}
nodAVL* rotatieStanga(nodAVL* rad) {
	if (rad != NULL) {
		nodAVL* nod1 = rad->dreapta;
		rad->dreapta = nod1->stanga;
		nod1->stanga = rad;
		rad = nod1;
		return rad;
	}
}

nodAVL* rotatieDreaptaStanga(nodAVL* rad) {
	rad->dreapta = rotatieDreapta(rad->dreapta);
	return rotatieStanga(rad);
}

nodAVL* rotatieStangaDreapta(nodAVL* rad) {
	rad->stanga = rotatieStanga(rad->stanga);
	return rotatieDreapta(rad);
}


void main() {
	nodAVL* rad = NULL;
	carte c;
	char buffer[20];
	int nrCarti;
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

	dezalocare(rad);
}