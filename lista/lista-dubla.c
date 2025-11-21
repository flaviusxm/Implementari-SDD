#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Disclaimer:
// Orice structura de date trebuie înteleasa logic
// Memorarea fara intelegere este ca alergatul în cerc — obosesti, dar nu ajungi nicaieri
// Codul de fata este o idee simpla de implementare pentru o Lista Dubla Inlantuita (LDI)

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


NodListaDubla* creareNodDubla(Afacere af) {
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

void inserareNodFinalLista(NodListaDubla** cap, Afacere af) {
    NodListaDubla* nou = creareNodDubla(af);
    if (*cap == NULL) {
        *cap = nou;
    } else {
        NodListaDubla* tempo_nod = *cap;
        while (tempo_nod->next != NULL) {
            tempo_nod = tempo_nod->next;
        }
        tempo_nod->next = nou;
        nou->prev = tempo_nod;
    }
}

void inserareNodInceputLista(NodListaDubla** cap, Afacere af) {
    NodListaDubla* nou = creareNodDubla(af);
    if (*cap == NULL) {
        *cap = nou;
    } else {
        nou->next = *cap;
        (*cap)->prev = nou;
        *cap = nou;
    }
}

void stergereNodDupaCui(NodListaDubla** cap, int cui) {
    if (*cap == NULL) return;
    NodListaDubla* nod_curent = *cap;
    while (nod_curent != NULL) {
        if (nod_curent->af.cui == cui) {
            if (nod_curent->prev != NULL) {
                nod_curent->prev->next = nod_curent->next;
            } else {
                *cap = nod_curent->next;
            }
            if (nod_curent->next != NULL) {
                nod_curent->next->prev = nod_curent->prev;
            }
            free(nod_curent->af.adresa);
            free(nod_curent->af.numeProprietar);
            free(nod_curent);
            return;
        }
        nod_curent = nod_curent->next;
    }
}


void dezalocareListaDubla(NodListaDubla** cap) {
    if(*cap == NULL) return;
    NodListaDubla* tempo_nod = *cap;
    while (tempo_nod != NULL) {
        NodListaDubla* aux_nod = tempo_nod;
        tempo_nod = tempo_nod->next;
        free(aux_nod->af.adresa);
        free(aux_nod->af.numeProprietar);
        free(aux_nod);
    }
    free((*cap)->af.adresa);
    free((*cap)->af.numeProprietar);
    free(*cap);
    *cap = NULL;
}

void afisareListaDublaInceputFinal(NodListaDubla* cap) {
   if (cap == NULL) return;
    NodListaDubla* tempo_nod = cap;
    while (tempo_nod != NULL) {
        printf("CUI: %d, Profit Anual Net: %.2f, Adresa: %s, Nume Proprietar: %s\n",
               tempo_nod->af.cui,
               tempo_nod->af.profitAnualNet,
               tempo_nod->af.adresa,
               tempo_nod->af.numeProprietar);
            if(tempo_nod->next == NULL) break;
        tempo_nod = tempo_nod->next;
    }
}

void afisareListaDublaFinalInceput(NodListaDubla* cap) {
    if (cap == NULL) return;
    NodListaDubla* tempo_nod = cap;
    while (tempo_nod->next != NULL) {
        tempo_nod = tempo_nod->next;
    }
    while (tempo_nod != NULL) {
        printf("CUI: %d, Profit Anual Net: %.2f, Adresa: %s, Nume Proprietar: %s\n",
               tempo_nod->af.cui,
               tempo_nod->af.profitAnualNet,
               tempo_nod->af.adresa,
               tempo_nod->af.numeProprietar);
        tempo_nod = tempo_nod->prev;
    }
}
int numarareNoduriListaDubla(NodListaDubla* cap) {
    int counter = 0;
    NodListaDubla* tempo_nod = cap;
    while (tempo_nod != NULL) {
        counter++;
        tempo_nod = tempo_nod->next;
    }
    return counter;
}

NodListaDubla* cautaDupaProprietar(NodListaDubla* cap, const char* nume) {
    NodListaDubla* temp = cap;
    while (temp != NULL) {
        if (strcmp(temp->af.numeProprietar, nume) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}
void stergereInceputListaDubla(NodListaDubla** cap) {
    if (*cap == NULL) return;
    NodListaDubla* nod_de_sters = *cap;
    *cap = (*cap)->next;
    if (*cap != NULL) {
        (*cap)->prev = NULL;
    }
    free(nod_de_sters->af.adresa);
    free(nod_de_sters->af.numeProprietar);
    free(nod_de_sters);
}   

void stergereFinalInceputListaDubla(NodListaDubla** cap) {
    if (*cap == NULL) return;
    NodListaDubla* tempo_nod = *cap;
    while (tempo_nod->next != NULL) {
        tempo_nod = tempo_nod->next;
    }
    if (tempo_nod->prev != NULL) {
        tempo_nod->prev->next = NULL;
    } else {
        *cap = NULL;
    }
    free(tempo_nod->af.adresa);
    free(tempo_nod->af.numeProprietar);
    free(tempo_nod);
}
 NodListaDubla*clonareListaDubla(NodListaDubla* cap) {
    if (cap == NULL) return NULL;
    NodListaDubla* nod_nou = NULL;
    NodListaDubla* nod_tempo = cap;
    while (nod_tempo != NULL) {
        inserareNodFinalLista(&nod_nou, nod_tempo->af);
        nod_tempo = nod_tempo->next;
    }
    return nod_nou;
}