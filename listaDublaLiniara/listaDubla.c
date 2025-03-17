#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* cod;
	char* nume;
	float medie;
}student;

typedef struct {
	student info;
	struct nodld* next;
	struct nodld* prev;
}nodld;


nodld* initializareNod(student s) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info.cod = (int*)malloc(sizeof(int));
	*(nou->info.cod) = *(s.cod);
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;
	nou->prev = NULL;
	nou->next = NULL;
	return nou;
}

nodld* inserareNod1(nodld* capld, nodld** coada, student s) {
	nodld* nou = initializareNod(s);
	if (capld == NULL) {
		capld = nou;
		*coada = nou;
	}
	else {
		(*coada)->next = nou;
		nou->prev = *coada;
		*coada = nou;
	}
	return capld;
}

void inserareNod2(nodld** capld, nodld** coada, student s) {
	nodld* nou = initializareNod(s);

	if (*capld == NULL) {
		*capld = nou;
		*coada = nou;
	}
	else {
		(*coada)->next = nou;
		nou->prev = *coada;
		*coada = nou;
	}
}

void traversare(nodld* capld) {
	nodld* temp = capld;
	while (temp != NULL) {
		printf("\n cod: %d, nume: %s, medie: %5.2f", *(temp->info.cod), temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareInvers(nodld* coada) {
	nodld* temp = coada;
	while (temp != NULL) {
		printf("\n cod: %d, nume: %s, medie: %5.2f", *(temp->info.cod), temp->info.nume, temp->info.medie);
		temp = temp->prev;
	}
}

void dezalocare(nodld* capld) {
	nodld* temp = capld;
	while (temp != NULL) {
		nodld* aux = temp->next;
		free(temp->info.cod);
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
}

void stergere(nodld** capld, nodld** coada, char* nume) {
	if (strcmp(((*capld)->info.nume), nume) == 0){
		nodld* temp = *capld;
		*capld = (*capld)->next;
		(*capld)->prev = NULL;
		
		free(temp->info.nume);
		free(temp->info.cod);
		free(temp);
		return;
	}
	else if (strcmp((*coada)->info.nume, nume) == 0) {
		nodld* temp = *coada;
		*coada = (*coada)->prev;
		(*coada)->prev = NULL;

		free(temp->info.nume);
		free(temp->info.cod);
		free(temp);
		return;
	}
	else {
		nodld* temp = *capld;
		while (temp != NULL) {
			if (strcmp(temp->info.nume, nume) == 0) {
				nodld* urmator = temp->next;
				nodld* anterior = temp->prev;

				urmator->prev = anterior;
				anterior->next = urmator;

				free(temp->info.nume);
				free(temp->info.cod);
				free(temp);
				return;
			}
			else {
				temp = temp->next;
			}
		}

	}
}
void main() {

	int nrstudenti;
	student s;
	char buffer[20];
	nodld* cap = NULL;
	nodld* coada = NULL;

	FILE* f = fopen("studenti.txt", "r");
	fscanf(f, "%d", &nrstudenti);
	for (int i = 0; i < nrstudenti; i++) {
		s.cod = (int*)malloc(sizeof(int));
		fscanf(f, "%d", s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		//cap = inserareNod1(cap, &coada, s);
		inserareNod2(&cap, &coada, s);
	}
	fclose(f);
	//traversare(cap);
	traversareInvers(coada);

	printf("\n--------------");
	stergere(&cap, &coada, "Maria");
	traversare(cap);
	dezalocare(cap);

}