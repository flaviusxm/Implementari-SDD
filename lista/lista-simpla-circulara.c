#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

// Disclaimer:
// Orice structura de date trebuie înteleasa logic
// Memorarea fara intelegere este ca alergatul în cerc — obosesti, dar nu ajungi nicaieri
// Codul de fata este o idee simpla de implementare pentru o Lista Simplu Inlantuita Circulara (LSIC)


 typedef struct Afacere {
    int cui;
    float profitAnualNet;
    char*adresa;
    char*numeProprietar;
}Afacere;

typedef struct NodListaSimpla{
    Afacere af;
    struct NodListaSimpla*next;
}NodListaSimpla;


NodListaSimpla*creareNod(Afacere af){
NodListaSimpla*nod=(NodListaSimpla*)malloc(sizeof(NodListaSimpla));
nod->af.cui=af.cui;
nod->af.profitAnualNet=af.profitAnualNet;
nod->af.adresa = (char*)malloc(strlen(af.adresa) + 1);
strcpy(nod->af.adresa, af.adresa);
nod->af.numeProprietar = (char*)malloc(strlen(af.numeProprietar) + 1);
strcpy(nod->af.numeProprietar, af.numeProprietar);
nod->next=NULL;
return nod;
}

void inserareFinal(NodListaSimpla**cap,Afacere af){
    NodListaSimpla*nou=creareNod(af);
    if(*cap==NULL){
    nou->next=nou;
    *cap=nou;
}else{
NodListaSimpla*tempo_nod=*cap;
while(tempo_nod!=*cap){
    tempo_nod=tempo_nod->next;
}
tempo_nod->next=nou;
nou->next=*cap;
}
}


void afisareListaSimplaCirculara(NodListaSimpla*cap){
    if(cap==NULL){
        printf("\n\nLista este goala ! ! !\n\n");
        return;
    }
    NodListaSimpla*tempo_nod=cap;
    do{
        printf("CUI : %d  -- Profit : %.2f -- Adresa : %s -- Proprietar : %s\n",tempo_nod->af.cui,tempo_nod->af.profitAnualNet,tempo_nod->af.adresa,tempo_nod->af.numeProprietar);
        tempo_nod=tempo_nod->next;
    }while(tempo_nod!=cap);

}
NodListaSimpla*cautaNodDupaCui(NodListaSimpla * cap,int cui){
    if(cap==NULL)return NULL;
    NodListaSimpla*tempo_nod=cap;
    do{
        if(tempo_nod->af.cui==cui){
            return tempo_nod;
        }
        tempo_nod=tempo_nod->next;
    }while(tempo_nod!=cap);
    return NULL;
}

int numarareNoduriListaSimpla(NodListaSimpla*cap){
    if(cap==NULL)return 0;
    int counter=0;
    NodListaSimpla*tempo_nod=cap;
    do{
        counter++;
        tempo_nod=tempo_nod->next;
    }while(tempo_nod!=cap);
    return counter;
}


void stergeNodDupaCui(NodListaSimpla**cap,int cui){
    if(*cap==NULL) return;
    NodListaSimpla*nod_curent=*cap;
    NodListaSimpla*nod_anterior=NULL;
    do{
        if(nod_curent->af.cui==cui){
            if(nod_curent==*cap && nod_curent->next==*cap){
                free(nod_curent->af.adresa);
                free(nod_curent->af.numeProprietar);
                free(nod_curent);
                *cap=NULL;
                return;
            }else if( nod_curent==*cap){
                NodListaSimpla*last_node=*cap;
                while(last_node->next!=*cap){
                    last_node=last_node->next;
                }
                last_node->next=nod_curent->next;
            }else{
                nod_anterior->next=nod_curent->next;
            }
            free(nod_curent->af.adresa);
            free(nod_curent->af.numeProprietar);
            free(nod_curent);
            return;
        }
        nod_anterior=nod_curent;
        nod_curent=nod_curent->next;
    }while(nod_curent!=*cap);
}

void dezalocareLista(NodListaSimpla**cap){
    if(*cap==NULL)return;
    NodListaSimpla*tempo_nod=(*cap)->next;
    while (tempo_nod!=*cap)
    {
        NodListaSimpla*aux_nod=tempo_nod;
        tempo_nod=tempo_nod->next;
        free(aux_nod->af.adresa);
        free(aux_nod->af.numeProprietar);
        free(aux_nod);
    }
    free((*cap)->af.adresa);
    free((*cap)->af.numeProprietar);
    free((*cap));
    *cap=NULL;

    
}

void salveazaListaSimplaFisier(NodListaSimpla*cap,const char*numeFisier){
    FILE*fisier=fopen(numeFisier,"w+");
        if(!fisier || cap==NULL)return;
        NodListaSimpla*nod_tempo=cap;
        do{
            fprintf(fisier,"\n\n %d %.2f %s %s \n\n",nod_tempo->af.cui,nod_tempo->af.profitAnualNet,nod_tempo->af.adresa,nod_tempo->af.numeProprietar);
            nod_tempo=nod_tempo->next;
        }while (nod_tempo!=cap);
        fclose(fisier);
}

NodListaSimpla* clonareListaSimpla(NodListaSimpla*cap){
    if(cap==NULL) return NULL;
    NodListaSimpla * nod_nou=NULL;
    NodListaSimpla*nod_tempo=cap;
    do{
        inserareFinal(&nod_nou,nod_tempo->af);
        nod_tempo=nod_tempo->next;
    }while(nod_tempo!=cap);
    return nod_nou;
}

void stergereNoduriIntervalCui(NodListaSimpla**cap,int cuiStart,int cuiStop){
    if(*cap==NULL)return;
    int nr_noduri_lista=numarareNoduriListaSimpla(*cap);
    for(int i=0;i<nr_noduri_lista;i++){
        NodListaSimpla*gasit=cautaNodDupaCui(*cap,cuiStart);
        if(gasit && gasit->af.cui>=cuiStart && gasit->af.cui<=cuiStop){
            stergeNodDupaCui(cap,gasit->af.cui);
        }
    }
}
void sortareDupaProfitListaSimpla(NodListaSimpla*cap){
    if(cap==NULL || cap->next==cap)return;
    bool check_schimbare=false;
NodListaSimpla*pointer_la_cap;
    do{
        check_schimbare=false;
            pointer_la_cap=cap;
            do{
                NodListaSimpla*nod_urmator=pointer_la_cap->next;
                if(nod_urmator!=cap && pointer_la_cap->af.profitAnualNet > nod_urmator->af.profitAnualNet){
                    Afacere af_temp=pointer_la_cap->af;
                    pointer_la_cap->af=nod_urmator->af;
                    nod_urmator->af=af_temp;
                    check_schimbare=true;
                }
                  pointer_la_cap=pointer_la_cap->next;
            }while(pointer_la_cap->next!=cap);
    }while(check_schimbare);
}
NodListaSimpla*afacereMaximProfit(NodListaSimpla*cap){
    if(cap==NULL)return;
    NodListaSimpla*max=cap;
    NodListaSimpla*nod_tempo=cap->next;
    while(nod_tempo!=cap){
        if(nod_tempo->af.profitAnualNet > max->af.profitAnualNet){
            max=nod_tempo;
        }
        nod_tempo=nod_tempo->next;
    }
    return max;
}