#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* nume;
	float medie;
}persoana;

typedef struct {
	persoana info;
	struct nodLS* next;
}nodLS;

typedef struct {
	nodLS** vect;
	int nrElem;
}hashT;

nodLS* initializareNod(persoana p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = p.cod;
	nou->info.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, p.nume);
	nou->info.medie = p.medie;
	nou->next = NULL;
	return nou;
}

void inserareNodLS(nodLS** cap, persoana p) {
	nodLS* nou = initializareNod(p);
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}


void traversareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		printf("\n cod: %d, nume: %s, medie: %5.2f", temp->info.cod, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp!= NULL) {
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
}

int functieHash1(int cheie, hashT tabela) {
	return cheie % tabela.nrElem;
}

int functieHash2(char* nume, hashT tabela) {
	return nume[0] % tabela.nrElem;
}


void inserareHash(hashT tabela, persoana p) {
	int poz = functieHash1(p.cod, tabela);
	inserareNodLS(&tabela.vect[poz], p);
}

void traversareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			printf("\n pozitia: %d", i);
			traversareLS(tabela.vect[i]);
		}
	}
}

void dezalocareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			dezalocareLS(tabela.vect[i]);
		}
		
	}
	free(tabela.vect);
}
void main() {
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++) {
		tabela.vect[i] = NULL;
	}
	persoana p;
	nodLS* cap = NULL;
	int nrPersoane;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrPersoane);
	for (int i = 0; i < nrPersoane; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		fscanf(f, "%f", &p.medie);

		inserareHash(tabela, p);
		
	}
	fclose(f);
	
	traversareHash(tabela);
	dezalocareHash(tabela);
}