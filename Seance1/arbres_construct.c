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
cell_lvlh_t* pref2lvlh(eltPrefPostFixee_t * tabEltPref,int* nbRacines)
{
    int fun =0;

    int* code= malloc(sizeof(int));
    cell_lvlh_t* nouv = NULL;
    eltType* eltPile = NULL;
    pile_t * pile = initPile(PILE_SZ);
    eltPrefPostFixee_t * courLc=tabEltPref;
    cell_lvlh_t* adrTete=allocPoint(courLc->val);
    cell_lvlh_t** pprec=&adrTete;
    int NB_fils_ou_frere= *nbRacines;
    courLc+=1;

    while (NB_fils_ou_frere>0 || !estVidePile(pile))
    {
        fprintf(stderr,"Tour : %d\n", fun);
        if(NB_fils_ou_frere>0){
            fprintf(stderr, "%c dans fils\n", courLc->val);
            fprintf(stderr, "pprec : %c dans fils\n", (*pprec)->val);
            fprintf(stderr, "%d dans fils\n", NB_fils_ou_frere);
            nouv = allocPoint(courLc->val);
            NB_fils_ou_frere= (courLc->nbFils);
            eltPile = malloc(sizeof(eltType));
            eltPile->adrCell=nouv;
            eltPile->adrPrec=(*pprec);
            eltPile->nbFils_ou_Freres=NB_fils_ou_frere-1;

            empiler(pile,eltPile, code);
            (*pprec)->lv=nouv;
            (*pprec)=nouv;
           
            courLc= courLc+1;

        }else{
            if(!estVidePile(pile)){
                fprintf(stderr, "%c dans frere\n", courLc->val);

                depiler(pile,eltPile,code);
                (*pprec)=eltPile->adrCell;
                fprintf(stderr, "pprec : %c dans frere\n", (*pprec)->val);
                // fprintf(stderr, "pprec : %c dans frere\n", pprec->val);
                // fprintf(stderr, "adrC : %c dans frere\n", eltPile->adrCell->val);
                nouv = allocPoint(courLc->val);
                (*pprec)->lh=nouv;
                NB_fils_ou_frere=eltPile->nbFils_ou_Freres;
                courLc= courLc+1;
            }
        }
        fun++;
    }
    libererPile(&pile);
    // free(eltPile->adrPrec);
    // free(eltPile->adrCell);
    // free(eltPile);
    return adrTete;
    

}

/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
//  libererArbre()
// {
// // TO DO
// }