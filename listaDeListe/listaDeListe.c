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
	struct nodLS* inf;
	struct nodLP* next;
}nodLP;


nodLS* initializareNodLS(persoana p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = p.cod;
	nou->info.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, p.nume);
	nou->info.medie = p.medie;
	nou->next = NULL;
	return nou;
}


void inserareNodLS(nodLS** cap, persoana p) {
	nodLS* nou = initializareNodLS(p);
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
		printf("\ncod: %d, nume: %s, medie: %5.2f", temp->info.cod, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
}


void inserareNodLP(nodLP** capLP, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL) {
		*capLP = nou;
	}
	else {
		nodLP* temp = *capLP;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareNodLP(nodLP* capLP) {
	nodLP* temp = capLP;
	int i = 0;
	while (temp != NULL) {
		printf("\n sublista %d", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLP(nodLP* capLP) {
	nodLP* temp = capLP;
	while (temp != NULL) {
		nodLP* aux = temp->next;
		dezalocare(temp->inf);
		free(temp);
		temp = aux;
	}
}
void main() {
	int nrPersoane;
	char buffer[20];
	nodLS* capLSPromovati = NULL;
	nodLS* capLSNepromovati = NULL;
	nodLP* capLP = NULL;
	persoana p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrPersoane);
	for (int i = 0; i < nrPersoane; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		fscanf(f, "%f", &p.medie);


		//criteriu de alegere lista
		if (p.medie >= 5) {
			inserareNodLS(&capLSPromovati, p);
		}
		else {
			inserareNodLS(&capLSNepromovati, p);
		}
		

	}
	fclose(f);
	//traversareLS(capLSPromovati);
	//printf("\n----------------------");
	//traversareLS(capLSNepromovati);


	inserareNodLP(&capLP, capLSNepromovati);
	inserareNodLP(&capLP, capLSPromovati);
	
	traversareNodLP(capLP);

	dezalocareLP(capLP);
}