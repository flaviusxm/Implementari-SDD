#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Disclaimer:
// Orice structura de date trebuie înteleasa logic
// Memorarea fara intelegere este ca alergatul în cerc — obosesti, dar nu ajungi nicaieri
// Codul de fata este o idee simpla de implementare pentru o Lista Dubla Inlantuita Circulara (LDIC)
typedef struct Afacere {
    int cui;
    float profitAnualNet;
    char* adresa;
    char* numeProprietar;
} Afacere;

typedef struct NodListaDubla {
    Afacere af;
    struct NodListaDubla* next;
    struct NodListaDubla* prev;
} NodListaDubla;
NodListaDubla* creareNodDublaCirculara(Afacere af) {
    NodListaDubla* nod = (NodListaDubla*)malloc(sizeof(NodListaDubla));
    nod->af.cui = af.cui;
    nod->af.profitAnualNet = af.profitAnualNet;
    nod->af.adresa = (char*)malloc(strlen(af.adresa) + 1);
    strcpy(nod->af.adresa, af.adresa);
    nod->af.numeProprietar = (char*)malloc(strlen(af.numeProprietar) + 1);
    strcpy(nod->af.numeProprietar, af.numeProprietar);
    nod->next = NULL;
    nod->prev = NULL;
    return nod;
}
NodListaDubla* inserareNodFinalListaDublaCirculara(NodListaDubla** cap, Afacere af) {
    NodListaDubla* nou = creareNodDublaCirculara(af);
    if (*cap == NULL) {
        nou->next = nou;
        nou->prev = nou;
        *cap = nou;
    } else {
        NodListaDubla* last = (*cap)->prev;
        last->next = nou;
        nou->prev = last;
        nou->next = *cap;
        (*cap)->prev = nou;
    }
    return *cap;
}
NodListaDubla* inserareNodInceputListaDublaCirculara(NodListaDubla** cap, Afacere af) {
    NodListaDubla* nou = creareNodDublaCirculara(af);
    if (*cap == NULL) {
        nou->next = nou;
        nou->prev = nou;
        *cap = nou;
    } else {
        NodListaDubla* last = (*cap)->prev;
        nou->next = *cap;
        nou->prev = last;
        last->next = nou;
        (*cap)->prev = nou;
        *cap = nou;
    }
    return *cap;
}
void afisareListaDublaCirculara(NodListaDubla* cap) {
    if (cap == NULL) {
        return;
    }
    NodListaDubla* tempo_nod = cap;
    do {
        printf("\n\n %d %.2f %s %s \n\n", tempo_nod->af.cui, tempo_nod->af.profitAnualNet,
               tempo_nod->af.adresa, tempo_nod->af.numeProprietar);
        tempo_nod = tempo_nod->next;
    } while (tempo_nod != cap);
}
void dezalocareListaDublaCirculara(NodListaDubla** cap) {
    if (*cap == NULL) return;
    NodListaDubla* tempo_nod = (*cap)->next;
    while (tempo_nod != *cap) {
        NodListaDubla* aux_nod = tempo_nod;
        tempo_nod = tempo_nod->next;
        free(aux_nod->af.adresa);
        free(aux_nod->af.numeProprietar);
        free(aux_nod);
    }
    free((*cap)->af.adresa);
    free((*cap)->af.numeProprietar);
    free((*cap));
    *cap = NULL;
}

int numarareNoduriListaDublaCirculara(NodListaDubla* cap) {
    if (cap == NULL) return 0;
    int counter = 0;
    NodListaDubla* tempo_nod = cap;
    do {
        counter++;
        tempo_nod = tempo_nod->next;
    } while (tempo_nod != cap);
    return counter;
}


NodListaDubla* cautaDupaCui(NodListaDubla* cap, int cui) {
    if (cap == NULL) return NULL;
    NodListaDubla* temp = cap;
    do {
        if (temp->af.cui == cui) return temp;
        temp = temp->next;
    } while (temp != cap);
    return NULL;
}


NodListaDubla* clonareLista(NodListaDubla* cap) {
    if (cap == NULL) return NULL;
    NodListaDubla* nouaLista = NULL;
    NodListaDubla* temp = cap;
    do {
        inserareNodFinalListaDublaCirculara(&nouaLista, temp->af);
        temp = temp->next;
    } while (temp != cap);
    return nouaLista;
}
