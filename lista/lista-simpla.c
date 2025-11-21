#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Disclaimer:
// Orice structura de date trebuie înteleasa logic
// Memorarea fara intelegere este ca alergatul în cerc — obosesti, dar nu ajungi nicaieri
// Codul de fata este o idee simpla de implementare pentru o Lista Simpla Inlantuita (LSI)

typedef struct Afacere {
    int cui;
    float profitAnualNet;
    char* adresa;
    char* numeProprietar;
} Afacere;

typedef struct NodListaSimpla {
    Afacere af;
    struct NodListaSimpla* next;
} NodListaSimpla;



Afacere infiinteazaAfacere(int cui, float profit, const char* adresa, const char* nume) {
    Afacere af;
    af.adresa = (char*)malloc(strlen(adresa) + 1);
    af.numeProprietar = (char*)malloc(strlen(nume) + 1);
    strcpy(af.adresa, adresa);
    strcpy(af.numeProprietar, nume);
    af.cui = cui;
    af.profitAnualNet = profit;
    return af;
}

NodListaSimpla* insereazaNodInceput(NodListaSimpla** cap, Afacere af) {
    NodListaSimpla* nod_nou = (NodListaSimpla*)malloc(sizeof(NodListaSimpla));
    if (!nod_nou) {
        printf("Eroare alocare memorie!\n");
        return NULL;
    }
    nod_nou->af = af;
    nod_nou->next = *cap;
    *cap = nod_nou;
    return *cap;
}

NodListaSimpla* insereazaNodFinal(NodListaSimpla** cap, Afacere af) {
    NodListaSimpla* nod_nou = (NodListaSimpla*)malloc(sizeof(NodListaSimpla));
    if (!nod_nou) {
        printf("Eroare alocare memorie!\n");
        return NULL;
    }
    nod_nou->af = af;
    nod_nou->next = NULL;

    if (*cap == NULL) {
        *cap = nod_nou;
    } else {
        NodListaSimpla* temp = *cap;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = nod_nou;
    }
    return *cap;
}

void afiseazaListaSimpla(NodListaSimpla* cap) {
    NodListaSimpla* temp = cap;
    while (temp) {
        printf("CUI: %d | Profit: %.2f | Adresa: %s | Proprietar: %s\n",
               temp->af.cui, temp->af.profitAnualNet,
               temp->af.adresa, temp->af.numeProprietar);
        temp = temp->next;
    }
}

NodListaSimpla* cautaNodDupaCUI(NodListaSimpla* cap, int cuiCautat) {
    while (cap) {
        if (cap->af.cui == cuiCautat)
            return cap;
        cap = cap->next;
    }
    return NULL;
}

void stergeNodDupaCUI(NodListaSimpla** cap, int cuiCautat) {
    NodListaSimpla* temp = *cap;
    NodListaSimpla* anterior = NULL;

    while (temp && temp->af.cui != cuiCautat) {
        anterior = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Nod cu CUI %d nu a fost găsit.\n", cuiCautat);
        return;
    }

    if (anterior == NULL)
        *cap = temp->next;
    else
        anterior->next = temp->next;

    free(temp->af.adresa);
    free(temp->af.numeProprietar);
    free(temp);
    printf("Nod cu CUI %d a fost șters.\n", cuiCautat);
}

void stergeListaSimpla(NodListaSimpla** cap) {
    NodListaSimpla* temp = *cap;
    while (temp) {
        NodListaSimpla* urmator = temp->next;
        free(temp->af.adresa);
        free(temp->af.numeProprietar);
        free(temp);
        temp = urmator;
    }
    *cap = NULL;
    printf("Lista a fost ștearsă complet.\n");
}


Afacere citesteAfacereDeLaTastatura() {
    int cui;
    float profit;
    char adresa[100], nume[100];

    printf("CUI: "); scanf("%d", &cui);
    printf("Profit: "); scanf("%f", &profit);
    getchar(); 
    printf("Adresa: "); fgets(adresa, 100, stdin);
    printf("Proprietar: "); fgets(nume, 100, stdin);

    adresa[strcspn(adresa, "\n")] = '\0';
    nume[strcspn(nume, "\n")] = '\0';

    return infiinteazaAfacere(cui, profit, adresa, nume);
}


int main() {
    NodListaSimpla* lista = NULL;
    srand(time(NULL));
    Afacere af1 = infiinteazaAfacere(rand()%10000, 50000.0f, "Str. Libertatii 12", "Darius");
    Afacere af2 = infiinteazaAfacere(rand()%10000, 75000.0f, "Str. Victoriei 45", "Eliza");

    insereazaNodInceput(&lista, af1);
    insereazaNodFinal(&lista, af2);

    printf("\n\n Lista dupa inserari \n\n");
    afiseazaListaSimpla(lista);

    printf("\n\n Cautare dupa CUI 1002 \n\n");
    NodListaSimpla* gasit = cautaNodDupaCUI(lista, 1002);
    if (gasit)
        printf("Găsit: %s\n", gasit->af.numeProprietar);
    else
        printf("\n\n Afacerea nu a fost gasita \n\n");

    printf("\n\n Stergere dupa CUI \n\n");
    stergeNodDupaCUI(&lista, 1001);
    afiseazaListaSimpla(lista);

    printf("\n\n Stergere  lista \n\n");
    stergeListaSimpla(&lista);

    return 0;
}
