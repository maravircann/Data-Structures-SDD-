#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* cod;
	char* nume;
	float medie;
}utilizator;

typedef struct {
	utilizator info;
	struct nodLDC* prev, * next;
}nodLDC;

nodLDC* initializareNod(utilizator u) {
	nodLDC* nou = (nodLDC*)malloc(sizeof(nodLDC));
	nou->info.cod = (int*)malloc(sizeof(int));
	*(nou->info.cod) = *(u.cod);
	nou->info.nume = (char*)malloc((strlen(u.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, u.nume);
	nou->info.medie = u.medie;
	nou->next = nou;
	nou->prev = nou;
	return nou;
}

void inserareNod(nodLDC** cap, utilizator u) {
	nodLDC* nou = initializareNod(u);
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLDC* ultim=(*cap)->prev;

		ultim->next = nou;
		nou->prev = ultim;

		nou->next = *cap;
		(*cap)->prev = nou;
	}
}

void traversare(nodLDC* cap) {
	nodLDC* temp = cap;
	while (temp->next != cap) {
		printf("\n cod: %d, nume: %s, medie: %5.2f", *(temp->info.cod), temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
	printf("\n cod: %d, nume: %s, medie: %5.2f", *(temp->info.cod), temp->info.nume, temp->info.medie);
}


void dezalocare(nodLDC* cap) {
	nodLDC* temp = cap;
	while (temp->next != cap) {
		nodLDC* aux = temp->next;
		free(temp->info.cod);
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
	free(temp->info.cod);
	free(temp->info.nume);
	free(temp);

}

void salvareUtilizatoriPromovati(nodLDC* cap, utilizator* vector, int* nrElem, float prag) {
	nodLDC* temp = cap;
	while (temp->next != cap) {
		if (temp->info.medie >= prag) {
			vector[*nrElem].cod = (int*)malloc(sizeof(int));
			*(vector[*nrElem].cod) = *(temp->info.cod);
			vector[*nrElem].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vector[*nrElem].nume, temp->info.nume);
			vector[*nrElem].medie = temp->info.medie;

			(*nrElem)++;
		}
		temp = temp->next;
	}
	if (temp->info.medie >= prag) {
		vector[*nrElem].cod = (int*)malloc(sizeof(int));
		*(vector[*nrElem].cod) = *(temp->info.cod);
		vector[*nrElem].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
		strcpy(vector[*nrElem].nume, temp->info.nume);
		vector[*nrElem].medie = temp->info.medie;

		(*nrElem)++;
	}
}

void stergereDupaNume(nodLDC** cap, char* nume) {
	if (strcmp((*cap)->info.nume, nume) == 0) {
		nodLDC* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.cod);
		free(temp->info.nume);
		free(temp);
		return;
	}
	else {
		nodLDC* temp = (*cap)->next;
		while (temp != *cap) {
			if (strcmp(temp->info.nume, nume) == 0) {
				nodLDC* anterior = temp->prev;
				nodLDC* urmator = temp->next;

				anterior->next = urmator;
				urmator->prev = anterior;

				free(temp->info.cod);
				free(temp->info.nume);
				free(temp);
				return;
			}
			temp = temp->next;
		}
	}
}
void main() {
	int nrUtilizatori;
	char buffer[20];
	utilizator u;
	nodLDC* cap = NULL;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrUtilizatori);
	for (int i = 0; i < nrUtilizatori; i++) {
		u.cod = (int*)malloc(sizeof(int));
		fscanf(f, "%d", u.cod);
		fscanf(f, "%s", buffer);
		u.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(u.nume, buffer);
		fscanf(f, "%f", &u.medie);

		inserareNod(&cap, u);
	}
	fclose(f);
	traversare(cap);
	int nr = 0;
	utilizator* vector = (utilizator*)malloc(nrUtilizatori * sizeof(utilizator));
	salvareUtilizatoriPromovati(cap, vector, &nr, 5);
	printf("\n------------utilizatori promovati-----------");
	for (int i = 0; i < nr; i++) {
		printf("\ncod: %d, nume: %s, medie: %5.2f", *(vector[i].cod), vector[i].nume, vector[i].medie);
	}
	printf("\n------------utilizatori dupa stergere-----------");
	stergereDupaNume(&cap, "ion");
	traversare(cap);

	dezalocare(cap);
}