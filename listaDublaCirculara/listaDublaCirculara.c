#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* cod;
	char* denumire;
	float pret;
}produs;

typedef struct {
	produs info;
	struct nodLDC* prev;
	struct nodLDC* next;
}nodLDC;

nodLDC* initializareNod(produs p) {
	nodLDC* nou = (nodLDC*)malloc(sizeof(nodLDC));

	nou->info.cod = (int*)malloc(sizeof(int));
	*(nou->info.cod) = *(p.cod);

	nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, p.denumire);

	nou->info.pret = p.pret;

	nou->next = NULL;
	nou->prev = NULL;

	return nou;
}


nodLDC* inserareNod(nodLDC* capLD, nodLDC** coada, produs p) {
	nodLDC* nou = initializareNod(p);

	if (capLD == NULL) {
		capLD = nou;
		*coada = nou;
	}
	else {
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
		(*coada)->next = capLD;
		capLD->prev = *coada;
	
	}
	return capLD;
}


void inserareNod2(nodLDC** capLD, nodLDC** coada, produs p) {
	nodLDC* nou = initializareNod(p);
	if (*capLD == NULL) {
		*capLD = nou;
		*coada = nou;
	}
	else {
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
		(*coada)->next = *capLD;
		(*capLD)->prev = *coada;
	}
}

void traversare(nodLDC* capLD) {
	nodLDC* temp = capLD;
	while (temp->next != capLD) {
		printf("\n cod: %d, denuimre: %s, pret: %5.2f", *(temp->info.cod), temp->info.denumire, temp->info.pret);
		temp = temp->next;
	}
	printf("\n cod: %d, denuimre: %s, pret: %5.2f", *(temp->info.cod), temp->info.denumire, temp->info.pret);
}

void traversareInvers(nodLDC* coada) {
	nodLDC* temp = coada;
	while (temp->prev != coada) {
		printf("\n cod: %d, denuimre: %s, pret: %5.2f", *(temp->info.cod), temp->info.denumire, temp->info.pret);
		temp = temp->prev;
	}
	printf("\n cod: %d, denuimre: %s, pret: %5.2f", *(temp->info.cod), temp->info.denumire, temp->info.pret);
}

void dezalocare(nodLDC* capLD) {
	nodLDC* temp = capLD;
	while (temp->next != capLD) {
		nodLDC* aux = temp->next;
		free(temp->info.cod);
		free(temp->info.denumire);
		free(temp);
		temp = aux;
	}
	free(temp->info.cod);
	free(temp->info.denumire);
	free(temp);
}

void salvareProduseVector(nodLDC* capLD, produs* vector, int* nrElem, float prag) {
	nodLDC* temp = capLD;
	while (temp->next != capLD) {
		if (temp->info.pret >= prag){
			vector[*nrElem].cod=(int*)malloc(sizeof(int));
			*(vector[*nrElem].cod)=*(temp->info.cod);

			vector[*nrElem].denumire = (char*)malloc((strlen(temp->info.denumire) + 1) * sizeof(char));
			strcpy(vector[*nrElem].denumire, temp->info.denumire);

			vector[*nrElem].pret = temp->info.pret;

			(*nrElem)++;
		}
		temp = temp->next;

	}
	if (temp->info.pret >= prag) {
		vector[*nrElem].cod = (int*)malloc(sizeof(int));
		*(vector[*nrElem].cod) = *(temp->info.cod);

		vector[*nrElem].denumire = (char*)malloc((strlen(temp->info.denumire) + 1) * sizeof(char));
		strcpy(vector[*nrElem].denumire, temp->info.denumire);

		vector[*nrElem].pret = temp->info.pret;

		(*nrElem)++;
	}
}


void stergereDupaDenumire(nodLDC** capLD, nodLDC** coada, char* denumire) {
	if (strcmp((*capLD)->info.denumire, denumire) == 0) {
		nodLDC* temp = *capLD;
		capLD = (*capLD)->next;
		(*capLD)->prev = *coada;
		(*coada)->next = *capLD;

		free(temp->info.cod);
		free(temp->info.denumire);
		free(temp);
		return;
	}
	else if (strcmp((*coada)->info.denumire, denumire) == 0) {
		nodLDC* temp = *coada;
		*coada = (*coada)->prev;
		(*coada)->next = *capLD;
		(*capLD)->prev = *coada;
		
		free(temp->info.cod);
		free(temp->info.denumire);
		free(temp);
		return;
	}
	else {
		nodLDC* temp = (*capLD)->next;
		while (temp!= *capLD) {

			if (strcmp(temp->info.denumire, denumire) == 0) {
				nodLDC* urmator = temp->next;
				nodLDC* anterior = temp->prev;

				urmator->prev = anterior;
				anterior->next = urmator;

				free(temp->info.cod);
				free(temp->info.denumire);
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
	int nrProduse;
	char buffer[20];
	produs p;
	FILE* f = fopen("fisier.txt", "r");
	nodLDC* cap = NULL;
	nodLDC* coada = NULL;
	fscanf(f, "%d", &nrProduse);
	for (int i = 0; i < nrProduse; i++) {
		 p.cod = (int*)malloc(sizeof(int));
		 fscanf(f, "%d", p.cod);

		 fscanf(f, "%s", buffer);
		 p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		 strcpy(p.denumire, buffer);

		 fscanf(f, "%f", &p.pret);


		// cap = inserareNod(cap, &coada, p);
		 inserareNod2(&cap, &coada, p);

	}
	fclose(f);
	printf("\n-----------traversare normala----------");
	traversare(cap);
	printf("\n-----------traversare inversa----------");
	traversareInvers(coada);

	printf("\n-------vector------------");
	int nr = 0;
	produs* vector = (produs*)malloc(nrProduse * sizeof(produs));
	salvareProduseVector(cap, vector, &nr, 3.f);
	for (int i = 0; i < nr; i++) {
		printf("\n cod:%d, denuimre:%s, pret:%5.2f ", *(vector[i].cod), vector[i].denumire, vector[i].pret);

	}

	printf("\n -------------dupa stergere-------");
	stergereDupaDenumire(&cap, &coada, "zahar");
	traversare(cap);
	dezalocare(cap);
}