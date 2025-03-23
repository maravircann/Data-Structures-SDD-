#include<stdio.h>
#include<malloc.h>

typedef struct {
	int zi, luna, an;
}dataReceptionare;

typedef struct {
	
	dataReceptionare data;
	char* denumireNotificare;
	float durata;

}notificare;

typedef struct {
	notificare info;
	struct nodStiva* next;
}nodStiva;

typedef struct {
	notificare info;
	struct nodCoada* next;
}nodCoada;

void push(nodStiva** varf, notificare n) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.data.zi = n.data.zi;
	nou->info.data.luna = n.data.luna;
	nou->info.data.an = n.data.an;
	nou->info.denumireNotificare = (char*)malloc((strlen(n.denumireNotificare) + 1) * sizeof(char));
	strcpy(nou->info.denumireNotificare, n.denumireNotificare);
	nou->info.durata = n.durata;
	nou->next = NULL;
	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, notificare* notif) {
	if (*varf == NULL) {
		return -1;
	}
	else {
		(*notif).data.zi = (*varf)->info.data.zi;
		(*notif).data.luna = (*varf)->info.data.luna;
		(*notif).data.an = (*varf)->info.data.an;
		(*notif).denumireNotificare = (char*)malloc((strlen((*varf)->info.denumireNotificare) + 1) * sizeof(char));
		strcpy((*notif).denumireNotificare, (*varf)->info.denumireNotificare);
		(*notif).durata = (*varf)->info.durata;

		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->info.denumireNotificare);
		free(temp);
		return 0;
	}
}

void afisareStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		printf("\n data:%d/%d/%d, denumire: %s, durata: %5.2f", temp->info.data.zi, temp->info.data.luna, temp->info.data.an, temp->info.denumireNotificare, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocarestiva(nodStiva* varf) {
	notificare notif;
	while (pop(&varf, &notif) == 0) {
		free(notif.denumireNotificare);
	}
}


void put(nodCoada** prim, nodCoada** ultim, notificare n) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->info.data.zi = n.data.zi;
	nou->info.data.luna = n.data.luna;
	nou->info.data.an = n.data.an;
	nou->info.denumireNotificare = (char*)malloc((strlen(n.denumireNotificare) + 1) * sizeof(char));
	strcpy(nou->info.denumireNotificare, n.denumireNotificare);
	nou->info.durata = n.durata;
	nou->next = NULL;

	if (*prim == NULL || *ultim==NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}


int get(nodCoada** prim, nodCoada** ultim, notificare* notif) {
	if (*prim != NULL && *ultim != NULL) {
		(*notif).data.zi = (*prim)->info.data.zi;
		(*notif).data.luna = (*prim)->info.data.luna;
		(*notif).data.an = (*prim)->info.data.an;
		(*notif).denumireNotificare = (char*)malloc((strlen((*prim)->info.denumireNotificare) + 1) * sizeof(char));
		strcpy((*notif).denumireNotificare, (*prim)->info.denumireNotificare);
		(*notif).durata = (*prim)->info.durata;

		nodCoada* temp = *prim;
		*prim = (*prim)->next;

		free(temp->info.denumireNotificare);
		free(temp);

		return 0;
	}
	if (*prim == NULL) {
		*ultim = NULL;
		return -1;
	}

}

void afisareCoada(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp)
	{
		printf("\ndata: %d/%d/%d, denumire: %s, durata: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.denumireNotificare, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareCoada(nodCoada* prim, nodCoada* ultim) {
	notificare notif;
	while (get(&prim, &ultim, &notif) == 0) {
		free(notif.denumireNotificare);
	}
}


void conversieStivaCoada(nodStiva* varf, nodCoada** prim, nodCoada** ultim) {
	notificare notif;
	while (pop(&varf, &notif) == 0) {
		put(prim, ultim, notif);
	}
}

void determinareNotificariDurata(nodCoada* prim, nodCoada* ultim, notificare* vector, int* nr, float prag) {
	notificare notif;
	 while(get(&prim, &ultim, &notif) == 0) {
		if (notif.durata >= prag) {
			vector[*nr] = notif;
			(*nr)++;
		}
	}
}
void main() {

	int nrNotificari;
	char buffer[20];
	nodStiva* varf = NULL;
	notificare n;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrNotificari);
	for (int i = 0; i < nrNotificari; i++) {
		fscanf(f, "%d", &n.data.zi);
		fscanf(f, "%d", &n.data.luna);
		fscanf(f, "%d", &n.data.an);

		fscanf(f, "%s", buffer);
		n.denumireNotificare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(n.denumireNotificare, buffer);

		fscanf(f, "%f", &n.durata);

		push(&varf, n);

		//put(&prim, &ultim, n);


	}
	fclose(f);
	printf("\n-----------stiva------------");
	afisareStiva(varf);
	printf("\n-----------coada------------");
	conversieStivaCoada(varf, &prim, &ultim);
	afisareCoada(prim);

	printf("\n-----------vector------------");
	notificare* vector = (notificare*)malloc(nrNotificari * sizeof(notificare));
	int nr = 0;
	determinareNotificariDurata(prim, ultim, vector, &nr, 2);
	for (int i = 0; i < nr; i++) {
		printf("\ndata: %d/%d/%d, denumire: %s, durata: %5.2f",
			vector[i].data.zi, vector[i].data.luna, vector[i].data.an,
			vector[i].denumireNotificare, vector[i].durata);
	}

	for (int i = 0; i < nr; i++) {
		free(vector[i].denumireNotificare);
	}
	free(vector);
	//dezalocarestiva(varf);
	//dezalocareCoada(prim, ultim);
	
}