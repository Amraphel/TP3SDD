/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(char * fileName, eltPrefPostFixee_t* tabEltPref , int* nbEltsPref)
{
    int nbRacine = 0;
    char c ;
    
    if(tabEltPref && nbEltsPref){
        FILE * file = fopen(fileName, "r");
        *nbEltsPref = 0;

        if(file)
        {
            fscanf(file,"%d", &nbRacine);
            c = fgetc(file);
            while(c == ' ')
            {  
                fscanf(file, "%c %d", &tabEltPref[*nbEltsPref].val, &tabEltPref[*nbEltsPref].nbFils);
                *nbEltsPref +=1;
                c = fgetc(file);
            }
            fclose(file);
        }
    }
    return nbRacine;
}

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    int ind;
    for(ind=0; ind<nbEltsPref; ind++){
        fprintf(file, " (%c,%d)", tabEltPref[ind].val, tabEltPref[ind].nbFils);
    }
    fprintf(file,"\n");

}

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t *allocPoint(char val)
{
    cell_lvlh_t *nouv = malloc(sizeof(cell_lvlh_t));
    if(nouv)
    {
        nouv->val = val;
        nouv->lv = NULL;
        nouv->lh = NULL;
        //test
    }
    return nouv;
}

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
cell_lvlh_t* pref2lvlh(eltPrefPostFixee_t * tabEltPref,int nbRacines)
{
    int code=0;
    cell_lvlh_t* nouv = NULL;
    eltType eltPile;

    cell_lvlh_t* adrTete=NULL;
    cell_lvlh_t** pprec=&adrTete;

    pile_t * pile = initPile(PILE_SZ);
    eltPrefPostFixee_t * courLc=tabEltPref;
    int NB_fils_ou_frere= nbRacines;


    while (NB_fils_ou_frere>0 || !estVidePile(pile))
    {
        
        if(NB_fils_ou_frere>0){
            nouv = allocPoint(courLc->val);
            *pprec=nouv;
            
            eltPile.adrPrec=&(nouv->lh);
            eltPile.nbFils_ou_Freres=NB_fils_ou_frere-1;
            
            empiler(pile,&eltPile, &code);
            pprec=&(nouv->lv);
            NB_fils_ou_frere= (courLc->nbFils);
            courLc= courLc+1;

        }else{
            if(!estVidePile(pile)){
                depiler(pile,&eltPile,&code);
                pprec=eltPile.adrPrec;
                NB_fils_ou_frere=eltPile.nbFils_ou_Freres;
                //  fprintf(stderr,"Test : %d\n", NB_fils_ou_frere);
            }
        }
        
    }
    libererPile(&pile);
    return adrTete;
    

}


/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
void libererArbre(cell_lvlh_t** adrPtRacine)
{
    if((*adrPtRacine)){
        if((*adrPtRacine)->lv){
            libererArbre(&(*adrPtRacine)->lv);
        }
        if((*adrPtRacine)->lh){
            libererArbre(&(*adrPtRacine)->lh);
        }
        free(*adrPtRacine);

        *adrPtRacine=NULL;
    }

}